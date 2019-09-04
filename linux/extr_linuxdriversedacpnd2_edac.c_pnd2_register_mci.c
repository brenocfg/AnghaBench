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
struct pnd2_pvt {int dummy; } ;
struct mem_ctl_info {char* ctl_name; int /*<<< orphan*/  dev_name; int /*<<< orphan*/  mod_name; struct pnd2_pvt* pvt_info; } ;
struct edac_mc_layer {int is_virt_csrow; int /*<<< orphan*/  size; int /*<<< orphan*/  type; } ;
struct TYPE_2__ {int (* check_ecc ) () ;int /*<<< orphan*/  (* get_dimm_config ) (struct mem_ctl_info*) ;int /*<<< orphan*/  name; int /*<<< orphan*/  dimms_per_channel; int /*<<< orphan*/  channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct edac_mc_layer*) ; 
 int /*<<< orphan*/  EDAC_MC_LAYER_CHANNEL ; 
 int /*<<< orphan*/  EDAC_MC_LAYER_SLOT ; 
 int /*<<< orphan*/  EDAC_MOD_STR ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  edac_dbg (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ edac_mc_add_mc (struct mem_ctl_info*) ; 
 struct mem_ctl_info* edac_mc_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct edac_mc_layer*,int) ; 
 int /*<<< orphan*/  edac_mc_free (struct mem_ctl_info*) ; 
 int /*<<< orphan*/  memset (struct pnd2_pvt*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* ops ; 
 int stub1 () ; 
 int /*<<< orphan*/  stub2 (struct mem_ctl_info*) ; 

__attribute__((used)) static int pnd2_register_mci(struct mem_ctl_info **ppmci)
{
	struct edac_mc_layer layers[2];
	struct mem_ctl_info *mci;
	struct pnd2_pvt *pvt;
	int rc;

	rc = ops->check_ecc();
	if (rc < 0)
		return rc;

	/* Allocate a new MC control structure */
	layers[0].type = EDAC_MC_LAYER_CHANNEL;
	layers[0].size = ops->channels;
	layers[0].is_virt_csrow = false;
	layers[1].type = EDAC_MC_LAYER_SLOT;
	layers[1].size = ops->dimms_per_channel;
	layers[1].is_virt_csrow = true;
	mci = edac_mc_alloc(0, ARRAY_SIZE(layers), layers, sizeof(*pvt));
	if (!mci)
		return -ENOMEM;

	pvt = mci->pvt_info;
	memset(pvt, 0, sizeof(*pvt));

	mci->mod_name = EDAC_MOD_STR;
	mci->dev_name = ops->name;
	mci->ctl_name = "Pondicherry2";

	/* Get dimm basic config and the memory layout */
	ops->get_dimm_config(mci);

	if (edac_mc_add_mc(mci)) {
		edac_dbg(0, "MC: failed edac_mc_add_mc()\n");
		edac_mc_free(mci);
		return -EINVAL;
	}

	*ppmci = mci;

	return 0;
}