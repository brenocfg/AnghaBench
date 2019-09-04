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
typedef  int u32 ;
struct ppc4xx_edac_pdata {int dummy; } ;
struct TYPE_2__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct mem_ctl_info {int /*<<< orphan*/  pdev; } ;
struct edac_mc_layer {int is_virt_csrow; int /*<<< orphan*/  size; int /*<<< orphan*/  type; } ;
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  dcr_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct edac_mc_layer*) ; 
 int /*<<< orphan*/  EDAC_MC_LAYER_CHANNEL ; 
 int /*<<< orphan*/  EDAC_MC_LAYER_CHIP_SELECT ; 
 scalar_t__ EDAC_OPSTATE_INT ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  KERN_NOTICE ; 
 int /*<<< orphan*/  SDRAM_MCOPT1 ; 
 int SDRAM_MCOPT1_MCHK_MASK ; 
 int SDRAM_MCOPT1_MCHK_NON ; 
 scalar_t__ edac_mc_add_mc (struct mem_ctl_info*) ; 
 struct mem_ctl_info* edac_mc_alloc (int,int /*<<< orphan*/ ,struct edac_mc_layer*,int) ; 
 int /*<<< orphan*/  edac_mc_del_mc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edac_mc_free (struct mem_ctl_info*) ; 
 scalar_t__ edac_op_state ; 
 int mfsdram (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_device_is_compatible (struct device_node const*,char*) ; 
 int ppc4xx_edac_map_dcrs (struct device_node const*,int /*<<< orphan*/ *) ; 
 int ppc4xx_edac_mc_init (struct mem_ctl_info*,struct platform_device*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ppc4xx_edac_mc_printk (int /*<<< orphan*/ ,struct mem_ctl_info*,char*) ; 
 int /*<<< orphan*/  ppc4xx_edac_nr_chans ; 
 int /*<<< orphan*/  ppc4xx_edac_nr_csrows ; 
 int /*<<< orphan*/  ppc4xx_edac_printk (int /*<<< orphan*/ ,char*,...) ; 
 int ppc4xx_edac_register_irq (struct platform_device*,struct mem_ctl_info*) ; 

__attribute__((used)) static int ppc4xx_edac_probe(struct platform_device *op)
{
	int status = 0;
	u32 mcopt1, memcheck;
	dcr_host_t dcr_host;
	const struct device_node *np = op->dev.of_node;
	struct mem_ctl_info *mci = NULL;
	struct edac_mc_layer layers[2];
	static int ppc4xx_edac_instance;

	/*
	 * At this point, we only support the controller realized on
	 * the AMCC PPC 405EX[r]. Reject anything else.
	 */

	if (!of_device_is_compatible(np, "ibm,sdram-405ex") &&
	    !of_device_is_compatible(np, "ibm,sdram-405exr")) {
		ppc4xx_edac_printk(KERN_NOTICE,
				   "Only the PPC405EX[r] is supported.\n");
		return -ENODEV;
	}

	/*
	 * Next, get the DCR property and attempt to map it so that we
	 * can probe the controller.
	 */

	status = ppc4xx_edac_map_dcrs(np, &dcr_host);

	if (status)
		return status;

	/*
	 * First determine whether ECC is enabled at all. If not,
	 * there is no useful checking or monitoring that can be done
	 * for this controller.
	 */

	mcopt1 = mfsdram(&dcr_host, SDRAM_MCOPT1);
	memcheck = (mcopt1 & SDRAM_MCOPT1_MCHK_MASK);

	if (memcheck == SDRAM_MCOPT1_MCHK_NON) {
		ppc4xx_edac_printk(KERN_INFO, "%pOF: No ECC memory detected or "
				   "ECC is disabled.\n", np);
		status = -ENODEV;
		goto done;
	}

	/*
	 * At this point, we know ECC is enabled, allocate an EDAC
	 * controller instance and perform the appropriate
	 * initialization.
	 */
	layers[0].type = EDAC_MC_LAYER_CHIP_SELECT;
	layers[0].size = ppc4xx_edac_nr_csrows;
	layers[0].is_virt_csrow = true;
	layers[1].type = EDAC_MC_LAYER_CHANNEL;
	layers[1].size = ppc4xx_edac_nr_chans;
	layers[1].is_virt_csrow = false;
	mci = edac_mc_alloc(ppc4xx_edac_instance, ARRAY_SIZE(layers), layers,
			    sizeof(struct ppc4xx_edac_pdata));
	if (mci == NULL) {
		ppc4xx_edac_printk(KERN_ERR, "%pOF: "
				   "Failed to allocate EDAC MC instance!\n",
				   np);
		status = -ENOMEM;
		goto done;
	}

	status = ppc4xx_edac_mc_init(mci, op, &dcr_host, mcopt1);

	if (status) {
		ppc4xx_edac_mc_printk(KERN_ERR, mci,
				      "Failed to initialize instance!\n");
		goto fail;
	}

	/*
	 * We have a valid, initialized EDAC instance bound to the
	 * controller. Attempt to register it with the EDAC subsystem
	 * and, if necessary, register interrupts.
	 */

	if (edac_mc_add_mc(mci)) {
		ppc4xx_edac_mc_printk(KERN_ERR, mci,
				      "Failed to add instance!\n");
		status = -ENODEV;
		goto fail;
	}

	if (edac_op_state == EDAC_OPSTATE_INT) {
		status = ppc4xx_edac_register_irq(op, mci);

		if (status)
			goto fail1;
	}

	ppc4xx_edac_instance++;

	return 0;

 fail1:
	edac_mc_del_mc(mci->pdev);

 fail:
	edac_mc_free(mci);

 done:
	return status;
}