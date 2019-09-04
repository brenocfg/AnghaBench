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
struct skx_pvt {struct skx_imc* imc; } ;
struct skx_imc {struct mem_ctl_info* mci; TYPE_1__* chan; int /*<<< orphan*/  lmc; int /*<<< orphan*/  node_id; int /*<<< orphan*/  mc; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct mem_ctl_info {int mtype_cap; int /*<<< orphan*/  ctl_name; int /*<<< orphan*/ * pdev; int /*<<< orphan*/ * ctl_page_to_phys; int /*<<< orphan*/  dev_name; int /*<<< orphan*/  mod_name; void* edac_cap; void* edac_ctl_cap; struct skx_pvt* pvt_info; } ;
struct edac_mc_layer {int is_virt_csrow; int /*<<< orphan*/  size; int /*<<< orphan*/  type; } ;
struct TYPE_2__ {struct pci_dev* cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct edac_mc_layer*) ; 
 void* EDAC_FLAG_NONE ; 
 int /*<<< orphan*/  EDAC_MC_LAYER_CHANNEL ; 
 int /*<<< orphan*/  EDAC_MC_LAYER_SLOT ; 
 int /*<<< orphan*/  EDAC_MOD_STR ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MEM_FLAG_DDR4 ; 
 int MEM_FLAG_NVDIMM ; 
 int /*<<< orphan*/  NUM_CHANNELS ; 
 int /*<<< orphan*/  NUM_DIMMS ; 
 int /*<<< orphan*/  edac_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int edac_mc_add_mc (struct mem_ctl_info*) ; 
 struct mem_ctl_info* edac_mc_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct edac_mc_layer*,int) ; 
 int /*<<< orphan*/  edac_mc_free (struct mem_ctl_info*) ; 
 int /*<<< orphan*/  kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 int skx_get_dimm_config (struct mem_ctl_info*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int skx_register_mci(struct skx_imc *imc)
{
	struct mem_ctl_info *mci;
	struct edac_mc_layer layers[2];
	struct pci_dev *pdev = imc->chan[0].cdev;
	struct skx_pvt *pvt;
	int rc;

	/* allocate a new MC control structure */
	layers[0].type = EDAC_MC_LAYER_CHANNEL;
	layers[0].size = NUM_CHANNELS;
	layers[0].is_virt_csrow = false;
	layers[1].type = EDAC_MC_LAYER_SLOT;
	layers[1].size = NUM_DIMMS;
	layers[1].is_virt_csrow = true;
	mci = edac_mc_alloc(imc->mc, ARRAY_SIZE(layers), layers,
			    sizeof(struct skx_pvt));

	if (unlikely(!mci))
		return -ENOMEM;

	edac_dbg(0, "MC#%d: mci = %p\n", imc->mc, mci);

	/* Associate skx_dev and mci for future usage */
	imc->mci = mci;
	pvt = mci->pvt_info;
	pvt->imc = imc;

	mci->ctl_name = kasprintf(GFP_KERNEL, "Skylake Socket#%d IMC#%d",
				  imc->node_id, imc->lmc);
	if (!mci->ctl_name) {
		rc = -ENOMEM;
		goto fail0;
	}

	mci->mtype_cap = MEM_FLAG_DDR4 | MEM_FLAG_NVDIMM;
	mci->edac_ctl_cap = EDAC_FLAG_NONE;
	mci->edac_cap = EDAC_FLAG_NONE;
	mci->mod_name = EDAC_MOD_STR;
	mci->dev_name = pci_name(imc->chan[0].cdev);
	mci->ctl_page_to_phys = NULL;

	rc = skx_get_dimm_config(mci);
	if (rc < 0)
		goto fail;

	/* record ptr to the generic device */
	mci->pdev = &pdev->dev;

	/* add this new MC control structure to EDAC's list of MCs */
	if (unlikely(edac_mc_add_mc(mci))) {
		edac_dbg(0, "MC: failed edac_mc_add_mc()\n");
		rc = -EINVAL;
		goto fail;
	}

	return 0;

fail:
	kfree(mci->ctl_name);
fail0:
	edac_mc_free(mci);
	imc->mci = NULL;
	return rc;
}