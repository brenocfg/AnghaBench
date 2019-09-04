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
struct pci_dev {scalar_t__ is_virtfn; int /*<<< orphan*/  dev; } ;
struct genwqe_dev {scalar_t__ slu_unitcfg; scalar_t__ app_unitcfg; int is_privileged; int /*<<< orphan*/  app_name; struct pci_dev* pci_dev; } ;

/* Variables and functions */
 int EIO ; 
 int ENOENT ; 
 int GENWQE_SLU_ARCH_REQ ; 
 int /*<<< orphan*/  IO_APP_UNITCFG ; 
 scalar_t__ IO_ILLEGAL_VALUE ; 
 int /*<<< orphan*/  IO_SLU_BITSTREAM ; 
 int /*<<< orphan*/  IO_SLU_UNITCFG ; 
 scalar_t__ __genwqe_readq (struct genwqe_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int genwqe_get_slu_id (struct genwqe_dev*) ; 
 int /*<<< orphan*/  genwqe_read_app_id (struct genwqe_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int genwqe_read_ids(struct genwqe_dev *cd)
{
	int err = 0;
	int slu_id;
	struct pci_dev *pci_dev = cd->pci_dev;

	cd->slu_unitcfg = __genwqe_readq(cd, IO_SLU_UNITCFG);
	if (cd->slu_unitcfg == IO_ILLEGAL_VALUE) {
		dev_err(&pci_dev->dev,
			"err: SLUID=%016llx\n", cd->slu_unitcfg);
		err = -EIO;
		goto out_err;
	}

	slu_id = genwqe_get_slu_id(cd);
	if (slu_id < GENWQE_SLU_ARCH_REQ || slu_id == 0xff) {
		dev_err(&pci_dev->dev,
			"err: incompatible SLU Architecture %u\n", slu_id);
		err = -ENOENT;
		goto out_err;
	}

	cd->app_unitcfg = __genwqe_readq(cd, IO_APP_UNITCFG);
	if (cd->app_unitcfg == IO_ILLEGAL_VALUE) {
		dev_err(&pci_dev->dev,
			"err: APPID=%016llx\n", cd->app_unitcfg);
		err = -EIO;
		goto out_err;
	}
	genwqe_read_app_id(cd, cd->app_name, sizeof(cd->app_name));

	/*
	 * Is access to all registers possible? If we are a VF the
	 * answer is obvious. If we run fully virtualized, we need to
	 * check if we can access all registers. If we do not have
	 * full access we will cause an UR and some informational FIRs
	 * in the PF, but that should not harm.
	 */
	if (pci_dev->is_virtfn)
		cd->is_privileged = 0;
	else
		cd->is_privileged = (__genwqe_readq(cd, IO_SLU_BITSTREAM)
				     != IO_ILLEGAL_VALUE);

 out_err:
	return err;
}