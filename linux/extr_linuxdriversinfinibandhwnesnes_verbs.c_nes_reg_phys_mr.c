#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u64 ;
typedef  int u32 ;
typedef  int u16 ;
struct nes_vpbl {scalar_t__ pbl_pbase; TYPE_1__* pbl_vbase; } ;
struct nes_vnic {struct nes_device* nesdev; } ;
struct nes_root_vpbl {scalar_t__ pbl_pbase; int /*<<< orphan*/ * pbl_vbase; } ;
struct nes_pd {int dummy; } ;
struct ib_mr {int rkey; int lkey; } ;
struct nes_mr {struct ib_mr ibmr; int /*<<< orphan*/  mode; int /*<<< orphan*/  pbl_4k; int /*<<< orphan*/  pbls_used; } ;
struct nes_device {int /*<<< orphan*/  pcidev; struct nes_adapter* nesadapter; } ;
struct nes_adapter {int max_mr; int /*<<< orphan*/  allocated_mrs; } ;
struct ib_pd {int /*<<< orphan*/  device; } ;
typedef  int /*<<< orphan*/  next_stag_index ;
struct TYPE_3__ {void* pa_high; void* pa_low; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct ib_mr* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IWNES_MEMREG_TYPE_MEM ; 
 int /*<<< orphan*/  NES_DBG_MR ; 
 int /*<<< orphan*/  NES_RESOURCE_PHYS_MR ; 
 int PAGE_MASK ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  get_random_bytes (int*,int) ; 
 int /*<<< orphan*/  kfree (struct nes_mr*) ; 
 struct nes_mr* kzalloc (int,int /*<<< orphan*/ ) ; 
 int nes_alloc_resource (struct nes_adapter*,int /*<<< orphan*/ ,int,int*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nes_debug (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  nes_free_resource (struct nes_adapter*,int /*<<< orphan*/ ,int) ; 
 int nes_reg_mr (struct nes_device*,struct nes_pd*,int,int,struct nes_root_vpbl*,int,int,int,int,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* pci_alloc_consistent (int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,TYPE_1__*,scalar_t__) ; 
 struct nes_pd* to_nespd (struct ib_pd*) ; 
 struct nes_vnic* to_nesvnic (int /*<<< orphan*/ ) ; 

struct ib_mr *nes_reg_phys_mr(struct ib_pd *ib_pd, u64 addr, u64 size,
		int acc, u64 *iova_start)
{
	u64 region_length;
	struct nes_pd *nespd = to_nespd(ib_pd);
	struct nes_vnic *nesvnic = to_nesvnic(ib_pd->device);
	struct nes_device *nesdev = nesvnic->nesdev;
	struct nes_adapter *nesadapter = nesdev->nesadapter;
	struct nes_mr *nesmr;
	struct ib_mr *ibmr;
	struct nes_vpbl vpbl;
	struct nes_root_vpbl root_vpbl;
	u32 stag;
	unsigned long mask;
	u32 stag_index = 0;
	u32 next_stag_index = 0;
	u32 driver_key = 0;
	int err = 0;
	int ret = 0;
	u16 pbl_count = 0;
	u8 single_page = 1;
	u8 stag_key = 0;

	region_length = 0;
	vpbl.pbl_vbase = NULL;
	root_vpbl.pbl_vbase = NULL;
	root_vpbl.pbl_pbase = 0;

	get_random_bytes(&next_stag_index, sizeof(next_stag_index));
	stag_key = (u8)next_stag_index;

	driver_key = 0;

	next_stag_index >>= 8;
	next_stag_index %= nesadapter->max_mr;

	if ((addr ^ *iova_start) & ~PAGE_MASK)
		return ERR_PTR(-EINVAL);

	err = nes_alloc_resource(nesadapter, nesadapter->allocated_mrs, nesadapter->max_mr,
			&stag_index, &next_stag_index, NES_RESOURCE_PHYS_MR);
	if (err) {
		return ERR_PTR(err);
	}

	nesmr = kzalloc(sizeof(*nesmr), GFP_KERNEL);
	if (!nesmr) {
		nes_free_resource(nesadapter, nesadapter->allocated_mrs, stag_index);
		return ERR_PTR(-ENOMEM);
	}

	/* Allocate a 4K buffer for the PBL */
	vpbl.pbl_vbase = pci_alloc_consistent(nesdev->pcidev, 4096,
			&vpbl.pbl_pbase);
	nes_debug(NES_DBG_MR, "Allocating leaf PBL, va = %p, pa = 0x%016lX\n",
			vpbl.pbl_vbase, (unsigned long)vpbl.pbl_pbase);
	if (!vpbl.pbl_vbase) {
		nes_free_resource(nesadapter, nesadapter->allocated_mrs, stag_index);
		ibmr = ERR_PTR(-ENOMEM);
		kfree(nesmr);
		goto reg_phys_err;
	}


	mask = !size;

	if (mask & ~PAGE_MASK) {
		nes_free_resource(nesadapter, nesadapter->allocated_mrs, stag_index);
		nes_debug(NES_DBG_MR, "Invalid buffer addr or size\n");
		ibmr = ERR_PTR(-EINVAL);
		kfree(nesmr);
		goto reg_phys_err;
	}

	region_length += size;
	vpbl.pbl_vbase[0].pa_low = cpu_to_le32((u32)addr & PAGE_MASK);
	vpbl.pbl_vbase[0].pa_high = cpu_to_le32((u32)((((u64)addr) >> 32)));

	stag = stag_index << 8;
	stag |= driver_key;
	stag += (u32)stag_key;

	nes_debug(NES_DBG_MR, "Registering STag 0x%08X, VA = 0x%016lX,"
			" length = 0x%016lX, index = 0x%08X\n",
			stag, (unsigned long)*iova_start, (unsigned long)region_length, stag_index);

	/* Make the leaf PBL the root if only one PBL */
	root_vpbl.pbl_pbase = vpbl.pbl_pbase;

	if (single_page) {
		pbl_count = 0;
	} else {
		pbl_count = 1;
	}
	ret = nes_reg_mr(nesdev, nespd, stag, region_length, &root_vpbl,
			addr, pbl_count, 1, acc, iova_start,
			&nesmr->pbls_used, &nesmr->pbl_4k);

	if (ret == 0) {
		nesmr->ibmr.rkey = stag;
		nesmr->ibmr.lkey = stag;
		nesmr->mode = IWNES_MEMREG_TYPE_MEM;
		ibmr = &nesmr->ibmr;
	} else {
		kfree(nesmr);
		ibmr = ERR_PTR(-ENOMEM);
	}

reg_phys_err:
	/* single PBL case */
	pci_free_consistent(nesdev->pcidev, 4096, vpbl.pbl_vbase, vpbl.pbl_pbase);
	return ibmr;
}