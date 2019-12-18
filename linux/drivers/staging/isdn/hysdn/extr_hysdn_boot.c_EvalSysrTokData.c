#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned char u_char ;
struct TYPE_4__ {int debug_flags; unsigned char bchans; unsigned char faxchans; int /*<<< orphan*/  mac_addr; } ;
typedef  TYPE_1__ hysdn_card ;

/* Variables and functions */
 int LOG_POF_RECORD ; 
#define  SYSR_TOK_B_CHAN 130 
 unsigned char SYSR_TOK_END ; 
#define  SYSR_TOK_FAX_CHAN 129 
#define  SYSR_TOK_MAC_ADDR 128 
 int /*<<< orphan*/  hysdn_addlog (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char*,int) ; 

int
EvalSysrTokData(hysdn_card *card, unsigned char *cp, int len)
{
	u_char *p;
	u_char crc;

	if (card->debug_flags & LOG_POF_RECORD)
		hysdn_addlog(card, "SysReady Token data length %d", len);

	if (len < 2) {
		hysdn_addlog(card, "SysReady Token Data to short");
		return (1);
	}
	for (p = cp, crc = 0; p < (cp + len - 2); p++)
		if ((crc & 0x80))
			crc = (((u_char) (crc << 1)) + 1) + *p;
		else
			crc = ((u_char) (crc << 1)) + *p;
	crc = ~crc;
	if (crc != *(cp + len - 1)) {
		hysdn_addlog(card, "SysReady Token Data invalid CRC");
		return (1);
	}
	len--;			/* don't check CRC byte */
	while (len > 0) {

		if (*cp == SYSR_TOK_END)
			return (0);	/* End of Token stream */

		if (len < (*(cp + 1) + 2)) {
			hysdn_addlog(card, "token 0x%x invalid length %d", *cp, *(cp + 1));
			return (1);
		}
		switch (*cp) {
		case SYSR_TOK_B_CHAN:	/* 1 */
			if (*(cp + 1) != 1)
				return (1);	/* length invalid */
			card->bchans = *(cp + 2);
			break;

		case SYSR_TOK_FAX_CHAN:	/* 2 */
			if (*(cp + 1) != 1)
				return (1);	/* length invalid */
			card->faxchans = *(cp + 2);
			break;

		case SYSR_TOK_MAC_ADDR:	/* 3 */
			if (*(cp + 1) != 6)
				return (1);	/* length invalid */
			memcpy(card->mac_addr, cp + 2, 6);
			break;

		default:
			hysdn_addlog(card, "unknown token 0x%02x length %d", *cp, *(cp + 1));
			break;
		}
		len -= (*(cp + 1) + 2);		/* adjust len */
		cp += (*(cp + 1) + 2);	/* and pointer */
	}

	hysdn_addlog(card, "no end token found");
	return (1);
}