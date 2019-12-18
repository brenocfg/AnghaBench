#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct mthca_mpt_entry {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  max_order; } ;
struct TYPE_9__ {int /*<<< orphan*/ * mpt_base; int /*<<< orphan*/ * mtt_base; TYPE_4__ mtt_buddy; } ;
struct TYPE_10__ {int mpt_base; int mtt_base; int /*<<< orphan*/  mpt_alloc; TYPE_4__ mtt_buddy; TYPE_2__ tavor_fmr; TYPE_4__* fmr_mtt_buddy; } ;
struct TYPE_8__ {int num_mpts; int fmr_reserved_mtts; int num_mtt_segs; int mtt_seg_size; int reserved_mtts; int /*<<< orphan*/  reserved_mrws; } ;
struct mthca_dev {int mthca_flags; TYPE_3__ mr_table; TYPE_1__ limits; int /*<<< orphan*/  pdev; } ;
typedef  scalar_t__ phys_addr_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int MTHCA_FLAG_DDR_HIDDEN ; 
 int MTHCA_FLAG_FMR ; 
 int MTHCA_FLAG_SINAI_OPT ; 
 int fls (int) ; 
 void* ioremap (scalar_t__,int) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mthca_alloc_cleanup (int /*<<< orphan*/ *) ; 
 int mthca_alloc_init (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mthca_alloc_mtt_range (struct mthca_dev*,int,TYPE_4__*) ; 
 int mthca_buddy_alloc (TYPE_4__*,int) ; 
 int /*<<< orphan*/  mthca_buddy_cleanup (TYPE_4__*) ; 
 int mthca_buddy_init (TYPE_4__*,int) ; 
 int /*<<< orphan*/  mthca_dbg (struct mthca_dev*,char*) ; 
 int /*<<< orphan*/  mthca_is_memfree (struct mthca_dev*) ; 
 int /*<<< orphan*/  mthca_warn (struct mthca_dev*,char*,...) ; 
 int pci_resource_len (int /*<<< orphan*/ ,int) ; 
 scalar_t__ pci_resource_start (int /*<<< orphan*/ ,int) ; 

int mthca_init_mr_table(struct mthca_dev *dev)
{
	phys_addr_t addr;
	int mpts, mtts, err, i;

	err = mthca_alloc_init(&dev->mr_table.mpt_alloc,
			       dev->limits.num_mpts,
			       ~0, dev->limits.reserved_mrws);
	if (err)
		return err;

	if (!mthca_is_memfree(dev) &&
	    (dev->mthca_flags & MTHCA_FLAG_DDR_HIDDEN))
		dev->limits.fmr_reserved_mtts = 0;
	else
		dev->mthca_flags |= MTHCA_FLAG_FMR;

	if (dev->mthca_flags & MTHCA_FLAG_SINAI_OPT)
		mthca_dbg(dev, "Memory key throughput optimization activated.\n");

	err = mthca_buddy_init(&dev->mr_table.mtt_buddy,
			       fls(dev->limits.num_mtt_segs - 1));

	if (err)
		goto err_mtt_buddy;

	dev->mr_table.tavor_fmr.mpt_base = NULL;
	dev->mr_table.tavor_fmr.mtt_base = NULL;

	if (dev->limits.fmr_reserved_mtts) {
		i = fls(dev->limits.fmr_reserved_mtts - 1);

		if (i >= 31) {
			mthca_warn(dev, "Unable to reserve 2^31 FMR MTTs.\n");
			err = -EINVAL;
			goto err_fmr_mpt;
		}
		mpts = mtts = 1 << i;
	} else {
		mtts = dev->limits.num_mtt_segs;
		mpts = dev->limits.num_mpts;
	}

	if (!mthca_is_memfree(dev) &&
	    (dev->mthca_flags & MTHCA_FLAG_FMR)) {

		addr = pci_resource_start(dev->pdev, 4) +
			((pci_resource_len(dev->pdev, 4) - 1) &
			 dev->mr_table.mpt_base);

		dev->mr_table.tavor_fmr.mpt_base =
			ioremap(addr, mpts * sizeof(struct mthca_mpt_entry));

		if (!dev->mr_table.tavor_fmr.mpt_base) {
			mthca_warn(dev, "MPT ioremap for FMR failed.\n");
			err = -ENOMEM;
			goto err_fmr_mpt;
		}

		addr = pci_resource_start(dev->pdev, 4) +
			((pci_resource_len(dev->pdev, 4) - 1) &
			 dev->mr_table.mtt_base);

		dev->mr_table.tavor_fmr.mtt_base =
			ioremap(addr, mtts * dev->limits.mtt_seg_size);
		if (!dev->mr_table.tavor_fmr.mtt_base) {
			mthca_warn(dev, "MTT ioremap for FMR failed.\n");
			err = -ENOMEM;
			goto err_fmr_mtt;
		}
	}

	if (dev->limits.fmr_reserved_mtts) {
		err = mthca_buddy_init(&dev->mr_table.tavor_fmr.mtt_buddy, fls(mtts - 1));
		if (err)
			goto err_fmr_mtt_buddy;

		/* Prevent regular MRs from using FMR keys */
		err = mthca_buddy_alloc(&dev->mr_table.mtt_buddy, fls(mtts - 1));
		if (err)
			goto err_reserve_fmr;

		dev->mr_table.fmr_mtt_buddy =
			&dev->mr_table.tavor_fmr.mtt_buddy;
	} else
		dev->mr_table.fmr_mtt_buddy = &dev->mr_table.mtt_buddy;

	/* FMR table is always the first, take reserved MTTs out of there */
	if (dev->limits.reserved_mtts) {
		i = fls(dev->limits.reserved_mtts - 1);

		if (mthca_alloc_mtt_range(dev, i,
					  dev->mr_table.fmr_mtt_buddy) == -1) {
			mthca_warn(dev, "MTT table of order %d is too small.\n",
				  dev->mr_table.fmr_mtt_buddy->max_order);
			err = -ENOMEM;
			goto err_reserve_mtts;
		}
	}

	return 0;

err_reserve_mtts:
err_reserve_fmr:
	if (dev->limits.fmr_reserved_mtts)
		mthca_buddy_cleanup(&dev->mr_table.tavor_fmr.mtt_buddy);

err_fmr_mtt_buddy:
	if (dev->mr_table.tavor_fmr.mtt_base)
		iounmap(dev->mr_table.tavor_fmr.mtt_base);

err_fmr_mtt:
	if (dev->mr_table.tavor_fmr.mpt_base)
		iounmap(dev->mr_table.tavor_fmr.mpt_base);

err_fmr_mpt:
	mthca_buddy_cleanup(&dev->mr_table.mtt_buddy);

err_mtt_buddy:
	mthca_alloc_cleanup(&dev->mr_table.mpt_alloc);

	return err;
}