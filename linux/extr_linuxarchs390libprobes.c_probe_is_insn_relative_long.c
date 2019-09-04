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
typedef  int u16 ;

/* Variables and functions */

int probe_is_insn_relative_long(u16 *insn)
{
	/* Check if we have a RIL-b or RIL-c format instruction which
	 * we need to modify in order to avoid instruction emulation. */
	switch (insn[0] >> 8) {
	case 0xc0:
		if ((insn[0] & 0x0f) == 0x00) /* larl */
			return true;
		break;
	case 0xc4:
		switch (insn[0] & 0x0f) {
		case 0x02: /* llhrl  */
		case 0x04: /* lghrl  */
		case 0x05: /* lhrl   */
		case 0x06: /* llghrl */
		case 0x07: /* sthrl  */
		case 0x08: /* lgrl   */
		case 0x0b: /* stgrl  */
		case 0x0c: /* lgfrl  */
		case 0x0d: /* lrl    */
		case 0x0e: /* llgfrl */
		case 0x0f: /* strl   */
			return true;
		}
		break;
	case 0xc6:
		switch (insn[0] & 0x0f) {
		case 0x02: /* pfdrl  */
		case 0x04: /* cghrl  */
		case 0x05: /* chrl   */
		case 0x06: /* clghrl */
		case 0x07: /* clhrl  */
		case 0x08: /* cgrl   */
		case 0x0a: /* clgrl  */
		case 0x0c: /* cgfrl  */
		case 0x0d: /* crl    */
		case 0x0e: /* clgfrl */
		case 0x0f: /* clrl   */
			return true;
		}
		break;
	}
	return false;
}