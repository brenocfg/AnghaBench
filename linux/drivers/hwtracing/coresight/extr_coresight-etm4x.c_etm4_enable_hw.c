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
struct etmv4_config {int pe_sel; int cfg; int eventctrl0; int eventctrl1; int stall_ctrl; int ts_ctrl; int syncfreq; int ccctlr; int bb_ctrl; int vinst_ctrl; int viiectlr; int vissctlr; int vipcssctlr; int* seq_ctrl; int seq_rst; int seq_state; int ext_inp; int* cntrldvr; int* cntr_ctrl; int* cntr_val; int* res_ctrl; int* ss_ctrl; int* ss_status; int* ss_pe_cmp; int ctxid_mask0; int ctxid_mask1; int vmid_mask0; int vmid_mask1; int /*<<< orphan*/ * vmid_val; int /*<<< orphan*/ * ctxid_pid; int /*<<< orphan*/ * addr_acc; int /*<<< orphan*/ * addr_val; } ;
struct etmv4_drvdata {int trcid; int nrseqstate; int nr_cntr; int nr_resource; int nr_ss_cmp; int nr_addr_cmp; int numcidc; int numvmidc; int /*<<< orphan*/  cpu; scalar_t__ base; TYPE_1__* csdev; struct etmv4_config config; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_LOCK (scalar_t__) ; 
 int /*<<< orphan*/  CS_UNLOCK (scalar_t__) ; 
 scalar_t__ TRCACATRn (int) ; 
 scalar_t__ TRCACVRn (int) ; 
 scalar_t__ TRCAUXCTLR ; 
 scalar_t__ TRCBBCTLR ; 
 scalar_t__ TRCCCCTLR ; 
 scalar_t__ TRCCIDCCTLR0 ; 
 scalar_t__ TRCCIDCCTLR1 ; 
 scalar_t__ TRCCIDCVRn (int) ; 
 scalar_t__ TRCCNTCTLRn (int) ; 
 scalar_t__ TRCCNTRLDVRn (int) ; 
 scalar_t__ TRCCNTVRn (int) ; 
 scalar_t__ TRCCONFIGR ; 
 scalar_t__ TRCEVENTCTL0R ; 
 scalar_t__ TRCEVENTCTL1R ; 
 scalar_t__ TRCEXTINSELR ; 
 scalar_t__ TRCPDCR ; 
 int TRCPDCR_PU ; 
 scalar_t__ TRCPRGCTLR ; 
 scalar_t__ TRCPROCSELR ; 
 scalar_t__ TRCRSCTLRn (int) ; 
 scalar_t__ TRCSEQEVRn (int) ; 
 scalar_t__ TRCSEQRSTEVR ; 
 scalar_t__ TRCSEQSTR ; 
 scalar_t__ TRCSSCCRn (int) ; 
 scalar_t__ TRCSSCSRn (int) ; 
 scalar_t__ TRCSSPCICRn (int) ; 
 scalar_t__ TRCSTALLCTLR ; 
 int /*<<< orphan*/  TRCSTATR ; 
 int /*<<< orphan*/  TRCSTATR_IDLE_BIT ; 
 scalar_t__ TRCSYNCPR ; 
 scalar_t__ TRCTRACEIDR ; 
 scalar_t__ TRCTSCTLR ; 
 scalar_t__ TRCVICTLR ; 
 scalar_t__ TRCVIIECTLR ; 
 scalar_t__ TRCVIPCSSCTLR ; 
 scalar_t__ TRCVISSCTLR ; 
 scalar_t__ TRCVMIDCCTLR0 ; 
 scalar_t__ TRCVMIDCCTLR1 ; 
 scalar_t__ TRCVMIDCVRn (int) ; 
 int coresight_claim_device_unlocked (scalar_t__) ; 
 scalar_t__ coresight_timeout (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dsb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  etm4_os_unlock (struct etmv4_drvdata*) ; 
 int /*<<< orphan*/  isb () ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  sy ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 
 int /*<<< orphan*/  writeq_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int etm4_enable_hw(struct etmv4_drvdata *drvdata)
{
	int i, rc;
	struct etmv4_config *config = &drvdata->config;
	struct device *etm_dev = &drvdata->csdev->dev;

	CS_UNLOCK(drvdata->base);

	etm4_os_unlock(drvdata);

	rc = coresight_claim_device_unlocked(drvdata->base);
	if (rc)
		goto done;

	/* Disable the trace unit before programming trace registers */
	writel_relaxed(0, drvdata->base + TRCPRGCTLR);

	/* wait for TRCSTATR.IDLE to go up */
	if (coresight_timeout(drvdata->base, TRCSTATR, TRCSTATR_IDLE_BIT, 1))
		dev_err(etm_dev,
			"timeout while waiting for Idle Trace Status\n");

	writel_relaxed(config->pe_sel, drvdata->base + TRCPROCSELR);
	writel_relaxed(config->cfg, drvdata->base + TRCCONFIGR);
	/* nothing specific implemented */
	writel_relaxed(0x0, drvdata->base + TRCAUXCTLR);
	writel_relaxed(config->eventctrl0, drvdata->base + TRCEVENTCTL0R);
	writel_relaxed(config->eventctrl1, drvdata->base + TRCEVENTCTL1R);
	writel_relaxed(config->stall_ctrl, drvdata->base + TRCSTALLCTLR);
	writel_relaxed(config->ts_ctrl, drvdata->base + TRCTSCTLR);
	writel_relaxed(config->syncfreq, drvdata->base + TRCSYNCPR);
	writel_relaxed(config->ccctlr, drvdata->base + TRCCCCTLR);
	writel_relaxed(config->bb_ctrl, drvdata->base + TRCBBCTLR);
	writel_relaxed(drvdata->trcid, drvdata->base + TRCTRACEIDR);
	writel_relaxed(config->vinst_ctrl, drvdata->base + TRCVICTLR);
	writel_relaxed(config->viiectlr, drvdata->base + TRCVIIECTLR);
	writel_relaxed(config->vissctlr,
		       drvdata->base + TRCVISSCTLR);
	writel_relaxed(config->vipcssctlr,
		       drvdata->base + TRCVIPCSSCTLR);
	for (i = 0; i < drvdata->nrseqstate - 1; i++)
		writel_relaxed(config->seq_ctrl[i],
			       drvdata->base + TRCSEQEVRn(i));
	writel_relaxed(config->seq_rst, drvdata->base + TRCSEQRSTEVR);
	writel_relaxed(config->seq_state, drvdata->base + TRCSEQSTR);
	writel_relaxed(config->ext_inp, drvdata->base + TRCEXTINSELR);
	for (i = 0; i < drvdata->nr_cntr; i++) {
		writel_relaxed(config->cntrldvr[i],
			       drvdata->base + TRCCNTRLDVRn(i));
		writel_relaxed(config->cntr_ctrl[i],
			       drvdata->base + TRCCNTCTLRn(i));
		writel_relaxed(config->cntr_val[i],
			       drvdata->base + TRCCNTVRn(i));
	}

	/*
	 * Resource selector pair 0 is always implemented and reserved.  As
	 * such start at 2.
	 */
	for (i = 2; i < drvdata->nr_resource * 2; i++)
		writel_relaxed(config->res_ctrl[i],
			       drvdata->base + TRCRSCTLRn(i));

	for (i = 0; i < drvdata->nr_ss_cmp; i++) {
		writel_relaxed(config->ss_ctrl[i],
			       drvdata->base + TRCSSCCRn(i));
		writel_relaxed(config->ss_status[i],
			       drvdata->base + TRCSSCSRn(i));
		writel_relaxed(config->ss_pe_cmp[i],
			       drvdata->base + TRCSSPCICRn(i));
	}
	for (i = 0; i < drvdata->nr_addr_cmp; i++) {
		writeq_relaxed(config->addr_val[i],
			       drvdata->base + TRCACVRn(i));
		writeq_relaxed(config->addr_acc[i],
			       drvdata->base + TRCACATRn(i));
	}
	for (i = 0; i < drvdata->numcidc; i++)
		writeq_relaxed(config->ctxid_pid[i],
			       drvdata->base + TRCCIDCVRn(i));
	writel_relaxed(config->ctxid_mask0, drvdata->base + TRCCIDCCTLR0);
	writel_relaxed(config->ctxid_mask1, drvdata->base + TRCCIDCCTLR1);

	for (i = 0; i < drvdata->numvmidc; i++)
		writeq_relaxed(config->vmid_val[i],
			       drvdata->base + TRCVMIDCVRn(i));
	writel_relaxed(config->vmid_mask0, drvdata->base + TRCVMIDCCTLR0);
	writel_relaxed(config->vmid_mask1, drvdata->base + TRCVMIDCCTLR1);

	/*
	 * Request to keep the trace unit powered and also
	 * emulation of powerdown
	 */
	writel_relaxed(readl_relaxed(drvdata->base + TRCPDCR) | TRCPDCR_PU,
		       drvdata->base + TRCPDCR);

	/* Enable the trace unit */
	writel_relaxed(1, drvdata->base + TRCPRGCTLR);

	/* wait for TRCSTATR.IDLE to go back down to '0' */
	if (coresight_timeout(drvdata->base, TRCSTATR, TRCSTATR_IDLE_BIT, 0))
		dev_err(etm_dev,
			"timeout while waiting for Idle Trace Status\n");

	/*
	 * As recommended by section 4.3.7 ("Synchronization when using the
	 * memory-mapped interface") of ARM IHI 0064D
	 */
	dsb(sy);
	isb();

done:
	CS_LOCK(drvdata->base);

	dev_dbg(etm_dev, "cpu: %d enable smp call done: %d\n",
		drvdata->cpu, rc);
	return rc;
}