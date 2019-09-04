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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct amd64_pvt {int fam; int model; int /*<<< orphan*/  F2; } ;

/* Variables and functions */
 int EINVAL ; 
 int amd64_read_pci_cfg (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dct_ganging_enabled (struct amd64_pvt*) ; 
 int /*<<< orphan*/  f15h_select_dct (struct amd64_pvt*,int) ; 

__attribute__((used)) static inline int amd64_read_dct_pci_cfg(struct amd64_pvt *pvt, u8 dct,
					 int offset, u32 *val)
{
	switch (pvt->fam) {
	case 0xf:
		if (dct || offset >= 0x100)
			return -EINVAL;
		break;

	case 0x10:
		if (dct) {
			/*
			 * Note: If ganging is enabled, barring the regs
			 * F2x[1,0]98 and F2x[1,0]9C; reads reads to F2x1xx
			 * return 0. (cf. Section 2.8.1 F10h BKDG)
			 */
			if (dct_ganging_enabled(pvt))
				return 0;

			offset += 0x100;
		}
		break;

	case 0x15:
		/*
		 * F15h: F2x1xx addresses do not map explicitly to DCT1.
		 * We should select which DCT we access using F1x10C[DctCfgSel]
		 */
		dct = (dct && pvt->model == 0x30) ? 3 : dct;
		f15h_select_dct(pvt, dct);
		break;

	case 0x16:
		if (dct)
			return -EINVAL;
		break;

	default:
		break;
	}
	return amd64_read_pci_cfg(pvt->F2, offset, val);
}