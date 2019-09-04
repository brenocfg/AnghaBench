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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {struct pci_dev* pci_mc1; struct pci_dev* pci_mc0; } ;
struct sbridge_pvt {TYPE_1__ knl; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int EINVAL ; 
 int ENODEV ; 
 int GET_BITFIELD (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/ * knl_tad_dram_hi ; 
 int /*<<< orphan*/ * knl_tad_dram_limit_lo ; 
 int /*<<< orphan*/ * knl_tad_dram_offset_lo ; 
 int* knl_tad_ways ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sbridge_printk (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int knl_get_tad(const struct sbridge_pvt *pvt,
		const int entry,
		const int mc,
		u64 *offset,
		u64 *limit,
		int *ways)
{
	u32 reg_limit_lo, reg_offset_lo, reg_hi;
	struct pci_dev *pci_mc;
	int way_id;

	switch (mc) {
	case 0:
		pci_mc = pvt->knl.pci_mc0;
		break;
	case 1:
		pci_mc = pvt->knl.pci_mc1;
		break;
	default:
		WARN_ON(1);
		return -EINVAL;
	}

	pci_read_config_dword(pci_mc,
			knl_tad_dram_limit_lo[entry], &reg_limit_lo);
	pci_read_config_dword(pci_mc,
			knl_tad_dram_offset_lo[entry], &reg_offset_lo);
	pci_read_config_dword(pci_mc,
			knl_tad_dram_hi[entry], &reg_hi);

	/* Is this TAD entry enabled? */
	if (!GET_BITFIELD(reg_limit_lo, 0, 0))
		return -ENODEV;

	way_id = GET_BITFIELD(reg_limit_lo, 3, 5);

	if (way_id < ARRAY_SIZE(knl_tad_ways)) {
		*ways = knl_tad_ways[way_id];
	} else {
		*ways = 0;
		sbridge_printk(KERN_ERR,
				"Unexpected value %d in mc_tad_limit_lo wayness field\n",
				way_id);
		return -ENODEV;
	}

	/*
	 * The least significant 6 bits of base and limit are truncated.
	 * For limit, we fill the missing bits with 1s.
	 */
	*offset = ((u64) GET_BITFIELD(reg_offset_lo, 6, 31) << 6) |
				((u64) GET_BITFIELD(reg_hi, 0,  15) << 32);
	*limit = ((u64) GET_BITFIELD(reg_limit_lo,  6, 31) << 6) | 63 |
				((u64) GET_BITFIELD(reg_hi, 16, 31) << 32);

	return 0;
}