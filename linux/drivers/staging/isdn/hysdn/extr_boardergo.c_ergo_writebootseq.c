#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned char* Data; unsigned char Len; unsigned char WrPtr; unsigned char RdPtr; } ;
typedef  TYPE_1__ tDpramBootSpooler ;
struct HYSDN_CARD {int debug_flags; scalar_t__ dpram; } ;

/* Variables and functions */
 int ERR_BOOTSEQ_FAIL ; 
 int LOG_POF_CARD ; 
 int /*<<< orphan*/  hysdn_addlog (struct HYSDN_CARD*,char*,...) ; 

__attribute__((used)) static int
ergo_writebootseq(struct HYSDN_CARD *card, unsigned char *buf, int len)
{
	tDpramBootSpooler *sp = (tDpramBootSpooler *) card->dpram;
	unsigned char *dst;
	unsigned char buflen;
	int nr_write;
	unsigned char tmp_rdptr;
	unsigned char wr_mirror;
	int i;

	if (card->debug_flags & LOG_POF_CARD)
		hysdn_addlog(card, "ERGO: write boot seq len=%d ", len);

	dst = sp->Data;		/* point to data in spool structure */
	buflen = sp->Len;	/* maximum len of spooled data */
	wr_mirror = sp->WrPtr;	/* only once read */

	/* try until all bytes written or error */
	i = 0x1000;		/* timeout value */
	while (len) {

		/* first determine the number of bytes that may be buffered */
		do {
			tmp_rdptr = sp->RdPtr;	/* first read the pointer */
			i--;	/* decrement timeout */
		} while (i && (tmp_rdptr != sp->RdPtr));	/* wait for stable pointer */

		if (!i) {
			if (card->debug_flags & LOG_POF_CARD)
				hysdn_addlog(card, "ERGO: write boot seq timeout");
			return (-ERR_BOOTSEQ_FAIL);	/* value not stable -> timeout */
		}
		if ((nr_write = tmp_rdptr - wr_mirror - 1) < 0)
			nr_write += buflen;	/* now we got number of free bytes - 1 in buffer */

		if (!nr_write)
			continue;	/* no free bytes in buffer */

		if (nr_write > len)
			nr_write = len;		/* limit if last few bytes */
		i = 0x1000;	/* reset timeout value */

		/* now we know how much bytes we may put in the puffer */
		len -= nr_write;	/* we savely could adjust len before output */
		while (nr_write--) {
			*(dst + wr_mirror) = *buf++;	/* output one byte */
			if (++wr_mirror >= buflen)
				wr_mirror = 0;
			sp->WrPtr = wr_mirror;	/* announce the next byte to E1 */
		}		/* while (nr_write) */

	}			/* while (len) */
	return (0);
}