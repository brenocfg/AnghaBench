#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct gsm_mux {int state; size_t count; unsigned char* buf; size_t len; int escape; unsigned char control; size_t mru; int /*<<< orphan*/  bad_size; void* fcs; int /*<<< orphan*/  address; int /*<<< orphan*/  malformed; } ;

/* Variables and functions */
 unsigned char GSM1_ESCAPE ; 
 unsigned char GSM1_ESCAPE_BITS ; 
 unsigned char GSM1_SOF ; 
#define  GSM_ADDRESS 132 
#define  GSM_CONTROL 131 
#define  GSM_DATA 130 
#define  GSM_OVERRUN 129 
 int GSM_SEARCH ; 
#define  GSM_START 128 
 void* INIT_FCS ; 
 void* gsm_fcs_add (void*,unsigned char) ; 
 int /*<<< orphan*/  gsm_queue (struct gsm_mux*) ; 
 int /*<<< orphan*/  gsm_read_ea (int /*<<< orphan*/ *,unsigned char) ; 

__attribute__((used)) static void gsm1_receive(struct gsm_mux *gsm, unsigned char c)
{
	if (c == GSM1_SOF) {
		/* EOF is only valid in frame if we have got to the data state
		   and received at least one byte (the FCS) */
		if (gsm->state == GSM_DATA && gsm->count) {
			/* Extract the FCS */
			gsm->count--;
			gsm->fcs = gsm_fcs_add(gsm->fcs, gsm->buf[gsm->count]);
			gsm->len = gsm->count;
			gsm_queue(gsm);
			gsm->state  = GSM_START;
			return;
		}
		/* Any partial frame was a runt so go back to start */
		if (gsm->state != GSM_START) {
			gsm->malformed++;
			gsm->state = GSM_START;
		}
		/* A SOF in GSM_START means we are still reading idling or
		   framing bytes */
		return;
	}

	if (c == GSM1_ESCAPE) {
		gsm->escape = 1;
		return;
	}

	/* Only an unescaped SOF gets us out of GSM search */
	if (gsm->state == GSM_SEARCH)
		return;

	if (gsm->escape) {
		c ^= GSM1_ESCAPE_BITS;
		gsm->escape = 0;
	}
	switch (gsm->state) {
	case GSM_START:		/* First byte after SOF */
		gsm->address = 0;
		gsm->state = GSM_ADDRESS;
		gsm->fcs = INIT_FCS;
		/* Fall through */
	case GSM_ADDRESS:	/* Address continuation */
		gsm->fcs = gsm_fcs_add(gsm->fcs, c);
		if (gsm_read_ea(&gsm->address, c))
			gsm->state = GSM_CONTROL;
		break;
	case GSM_CONTROL:	/* Control Byte */
		gsm->fcs = gsm_fcs_add(gsm->fcs, c);
		gsm->control = c;
		gsm->count = 0;
		gsm->state = GSM_DATA;
		break;
	case GSM_DATA:		/* Data */
		if (gsm->count > gsm->mru) {	/* Allow one for the FCS */
			gsm->state = GSM_OVERRUN;
			gsm->bad_size++;
		} else
			gsm->buf[gsm->count++] = c;
		break;
	case GSM_OVERRUN:	/* Over-long - eg a dropped SOF */
		break;
	}
}