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
typedef  int u64 ;
typedef  int u32 ;
struct genwqe_dev {int dummy; } ;

/* Variables and functions */
 int GENWQE_UID_OFFS (int) ; 
 int IO_EXTENDED_DIAG_MAP (int) ; 
 int IO_EXTENDED_ERROR_POINTER ; 
 int __genwqe_readq (struct genwqe_dev*,int) ; 

int genwqe_ffdc_buff_size(struct genwqe_dev *cd, int uid)
{
	int entries = 0, ring, traps, traces, trace_entries;
	u32 eevptr_addr, l_addr, d_len, d_type;
	u64 eevptr, val, addr;

	eevptr_addr = GENWQE_UID_OFFS(uid) | IO_EXTENDED_ERROR_POINTER;
	eevptr = __genwqe_readq(cd, eevptr_addr);

	if ((eevptr != 0x0) && (eevptr != -1ull)) {
		l_addr = GENWQE_UID_OFFS(uid) | eevptr;

		while (1) {
			val = __genwqe_readq(cd, l_addr);

			if ((val == 0x0) || (val == -1ull))
				break;

			/* 38:24 */
			d_len  = (val & 0x0000007fff000000ull) >> 24;

			/* 39 */
			d_type = (val & 0x0000008000000000ull) >> 36;

			if (d_type) {	/* repeat */
				entries += d_len;
			} else {	/* size in bytes! */
				entries += d_len >> 3;
			}

			l_addr += 8;
		}
	}

	for (ring = 0; ring < 8; ring++) {
		addr = GENWQE_UID_OFFS(uid) | IO_EXTENDED_DIAG_MAP(ring);
		val = __genwqe_readq(cd, addr);

		if ((val == 0x0ull) || (val == -1ull))
			continue;

		traps = (val >> 24) & 0xff;
		traces = (val >> 16) & 0xff;
		trace_entries = val & 0xffff;

		entries += traps + (traces * trace_entries);
	}
	return entries;
}