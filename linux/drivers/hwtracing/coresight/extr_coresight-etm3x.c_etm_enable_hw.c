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
struct etm_config {int ctrl; int trigger_event; int startstop_ctrl; int enable_event; int enable_ctrl1; int fifofull_level; int* addr_val; int* addr_acctype; int* cntr_rld_val; int* cntr_event; int* cntr_rld_event; int* cntr_val; int seq_12_event; int seq_21_event; int seq_23_event; int seq_31_event; int seq_32_event; int seq_13_event; int seq_curr_state; int* ctxid_pid; int ctxid_mask; int sync_freq; int timestamp_event; } ;
struct etm_drvdata {int port_size; int nr_addr_cmp; int nr_cntr; int nr_ext_out; int nr_ctxid_cmp; int traceid; int /*<<< orphan*/  cpu; TYPE_1__* csdev; int /*<<< orphan*/  base; struct etm_config config; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CS_UNLOCK (int /*<<< orphan*/ ) ; 
 int ETM3X_SUPPORTED_OPTIONS ; 
 int /*<<< orphan*/  ETMACTRn (int) ; 
 int /*<<< orphan*/  ETMACVRn (int) ; 
 int /*<<< orphan*/  ETMAUXCR ; 
 int /*<<< orphan*/  ETMCIDCMR ; 
 int /*<<< orphan*/  ETMCIDCVRn (int) ; 
 int /*<<< orphan*/  ETMCNTENRn (int) ; 
 int /*<<< orphan*/  ETMCNTRLDEVRn (int) ; 
 int /*<<< orphan*/  ETMCNTRLDVRn (int) ; 
 int /*<<< orphan*/  ETMCNTVRn (int) ; 
 int /*<<< orphan*/  ETMCR ; 
 int ETMCR_ETM_EN ; 
 int /*<<< orphan*/  ETMEXTINSELR ; 
 int /*<<< orphan*/  ETMEXTOUTEVRn (int) ; 
 int /*<<< orphan*/  ETMFFLR ; 
 int /*<<< orphan*/  ETMSQ12EVR ; 
 int /*<<< orphan*/  ETMSQ13EVR ; 
 int /*<<< orphan*/  ETMSQ21EVR ; 
 int /*<<< orphan*/  ETMSQ23EVR ; 
 int /*<<< orphan*/  ETMSQ31EVR ; 
 int /*<<< orphan*/  ETMSQ32EVR ; 
 int /*<<< orphan*/  ETMSQR ; 
 int /*<<< orphan*/  ETMSYNCFR ; 
 int /*<<< orphan*/  ETMTECR1 ; 
 int /*<<< orphan*/  ETMTEEVR ; 
 int /*<<< orphan*/  ETMTRACEIDR ; 
 int /*<<< orphan*/  ETMTRIGGER ; 
 int /*<<< orphan*/  ETMTSEVR ; 
 int /*<<< orphan*/  ETMTSSCR ; 
 int /*<<< orphan*/  ETMVMIDCVR ; 
 int ETM_DEFAULT_EVENT_VAL ; 
 int coresight_claim_device_unlocked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  etm_clr_prog (struct etm_drvdata*) ; 
 int /*<<< orphan*/  etm_clr_pwrdwn (struct etm_drvdata*) ; 
 int /*<<< orphan*/  etm_os_unlock (struct etm_drvdata*) ; 
 int etm_readl (struct etm_drvdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  etm_set_prog (struct etm_drvdata*) ; 
 int /*<<< orphan*/  etm_set_pwrup (struct etm_drvdata*) ; 
 int /*<<< orphan*/  etm_writel (struct etm_drvdata*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int etm_enable_hw(struct etm_drvdata *drvdata)
{
	int i, rc;
	u32 etmcr;
	struct etm_config *config = &drvdata->config;

	CS_UNLOCK(drvdata->base);

	rc = coresight_claim_device_unlocked(drvdata->base);
	if (rc)
		goto done;

	/* Turn engine on */
	etm_clr_pwrdwn(drvdata);
	/* Apply power to trace registers */
	etm_set_pwrup(drvdata);
	/* Make sure all registers are accessible */
	etm_os_unlock(drvdata);

	etm_set_prog(drvdata);

	etmcr = etm_readl(drvdata, ETMCR);
	/* Clear setting from a previous run if need be */
	etmcr &= ~ETM3X_SUPPORTED_OPTIONS;
	etmcr |= drvdata->port_size;
	etmcr |= ETMCR_ETM_EN;
	etm_writel(drvdata, config->ctrl | etmcr, ETMCR);
	etm_writel(drvdata, config->trigger_event, ETMTRIGGER);
	etm_writel(drvdata, config->startstop_ctrl, ETMTSSCR);
	etm_writel(drvdata, config->enable_event, ETMTEEVR);
	etm_writel(drvdata, config->enable_ctrl1, ETMTECR1);
	etm_writel(drvdata, config->fifofull_level, ETMFFLR);
	for (i = 0; i < drvdata->nr_addr_cmp; i++) {
		etm_writel(drvdata, config->addr_val[i], ETMACVRn(i));
		etm_writel(drvdata, config->addr_acctype[i], ETMACTRn(i));
	}
	for (i = 0; i < drvdata->nr_cntr; i++) {
		etm_writel(drvdata, config->cntr_rld_val[i], ETMCNTRLDVRn(i));
		etm_writel(drvdata, config->cntr_event[i], ETMCNTENRn(i));
		etm_writel(drvdata, config->cntr_rld_event[i],
			   ETMCNTRLDEVRn(i));
		etm_writel(drvdata, config->cntr_val[i], ETMCNTVRn(i));
	}
	etm_writel(drvdata, config->seq_12_event, ETMSQ12EVR);
	etm_writel(drvdata, config->seq_21_event, ETMSQ21EVR);
	etm_writel(drvdata, config->seq_23_event, ETMSQ23EVR);
	etm_writel(drvdata, config->seq_31_event, ETMSQ31EVR);
	etm_writel(drvdata, config->seq_32_event, ETMSQ32EVR);
	etm_writel(drvdata, config->seq_13_event, ETMSQ13EVR);
	etm_writel(drvdata, config->seq_curr_state, ETMSQR);
	for (i = 0; i < drvdata->nr_ext_out; i++)
		etm_writel(drvdata, ETM_DEFAULT_EVENT_VAL, ETMEXTOUTEVRn(i));
	for (i = 0; i < drvdata->nr_ctxid_cmp; i++)
		etm_writel(drvdata, config->ctxid_pid[i], ETMCIDCVRn(i));
	etm_writel(drvdata, config->ctxid_mask, ETMCIDCMR);
	etm_writel(drvdata, config->sync_freq, ETMSYNCFR);
	/* No external input selected */
	etm_writel(drvdata, 0x0, ETMEXTINSELR);
	etm_writel(drvdata, config->timestamp_event, ETMTSEVR);
	/* No auxiliary control selected */
	etm_writel(drvdata, 0x0, ETMAUXCR);
	etm_writel(drvdata, drvdata->traceid, ETMTRACEIDR);
	/* No VMID comparator value selected */
	etm_writel(drvdata, 0x0, ETMVMIDCVR);

	etm_clr_prog(drvdata);

done:
	CS_LOCK(drvdata->base);

	dev_dbg(&drvdata->csdev->dev, "cpu: %d enable smp call done: %d\n",
		drvdata->cpu, rc);
	return rc;
}