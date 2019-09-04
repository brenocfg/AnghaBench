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
struct etmv4_config {int mode; int cfg; int eventctrl0; int eventctrl1; int ts_ctrl; int stall_ctrl; int syncfreq; int vinst_ctrl; int viiectlr; int vissctlr; int* seq_ctrl; int seq_rst; int seq_state; int ext_inp; int cntr_idx; int* cntrldvr; int* cntr_ctrl; int* cntr_val; int res_idx; int* res_ctrl; int* ss_ctrl; int* ss_pe_cmp; int addr_idx; int* addr_val; int* addr_acc; int ctxid_idx; int* ctxid_pid; int ctxid_mask0; int ctxid_mask1; int vmid_idx; int* vmid_val; int vmid_mask0; int vmid_mask1; int /*<<< orphan*/ * addr_type; } ;
struct etmv4_drvdata {int syncpr; int nr_addr_cmp; int nrseqstate; int nr_cntr; int nr_resource; int nr_ss_cmp; int numcidc; int numvmidc; int /*<<< orphan*/  spinlock; scalar_t__ cpu; scalar_t__ trcid; struct etmv4_config config; } ;
struct device_attribute {int dummy; } ;
struct device {int /*<<< orphan*/  parent; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int BIT (int) ; 
 size_t EINVAL ; 
 int /*<<< orphan*/  ETM_ADDR_TYPE_NONE ; 
 int ETM_MODE_DATA_TRACE_ADDR ; 
 int ETM_MODE_DATA_TRACE_VAL ; 
 int ETM_MODE_LOAD ; 
 int ETM_MODE_STORE ; 
 int ETM_MODE_VIEWINST_STARTSTOP ; 
 struct etmv4_drvdata* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 scalar_t__ kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t reset_store(struct device *dev,
			   struct device_attribute *attr,
			   const char *buf, size_t size)
{
	int i;
	unsigned long val;
	struct etmv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	struct etmv4_config *config = &drvdata->config;

	if (kstrtoul(buf, 16, &val))
		return -EINVAL;

	spin_lock(&drvdata->spinlock);
	if (val)
		config->mode = 0x0;

	/* Disable data tracing: do not trace load and store data transfers */
	config->mode &= ~(ETM_MODE_LOAD | ETM_MODE_STORE);
	config->cfg &= ~(BIT(1) | BIT(2));

	/* Disable data value and data address tracing */
	config->mode &= ~(ETM_MODE_DATA_TRACE_ADDR |
			   ETM_MODE_DATA_TRACE_VAL);
	config->cfg &= ~(BIT(16) | BIT(17));

	/* Disable all events tracing */
	config->eventctrl0 = 0x0;
	config->eventctrl1 = 0x0;

	/* Disable timestamp event */
	config->ts_ctrl = 0x0;

	/* Disable stalling */
	config->stall_ctrl = 0x0;

	/* Reset trace synchronization period  to 2^8 = 256 bytes*/
	if (drvdata->syncpr == false)
		config->syncfreq = 0x8;

	/*
	 * Enable ViewInst to trace everything with start-stop logic in
	 * started state. ARM recommends start-stop logic is set before
	 * each trace run.
	 */
	config->vinst_ctrl |= BIT(0);
	if (drvdata->nr_addr_cmp == true) {
		config->mode |= ETM_MODE_VIEWINST_STARTSTOP;
		/* SSSTATUS, bit[9] */
		config->vinst_ctrl |= BIT(9);
	}

	/* No address range filtering for ViewInst */
	config->viiectlr = 0x0;

	/* No start-stop filtering for ViewInst */
	config->vissctlr = 0x0;

	/* Disable seq events */
	for (i = 0; i < drvdata->nrseqstate-1; i++)
		config->seq_ctrl[i] = 0x0;
	config->seq_rst = 0x0;
	config->seq_state = 0x0;

	/* Disable external input events */
	config->ext_inp = 0x0;

	config->cntr_idx = 0x0;
	for (i = 0; i < drvdata->nr_cntr; i++) {
		config->cntrldvr[i] = 0x0;
		config->cntr_ctrl[i] = 0x0;
		config->cntr_val[i] = 0x0;
	}

	config->res_idx = 0x0;
	for (i = 0; i < drvdata->nr_resource; i++)
		config->res_ctrl[i] = 0x0;

	for (i = 0; i < drvdata->nr_ss_cmp; i++) {
		config->ss_ctrl[i] = 0x0;
		config->ss_pe_cmp[i] = 0x0;
	}

	config->addr_idx = 0x0;
	for (i = 0; i < drvdata->nr_addr_cmp * 2; i++) {
		config->addr_val[i] = 0x0;
		config->addr_acc[i] = 0x0;
		config->addr_type[i] = ETM_ADDR_TYPE_NONE;
	}

	config->ctxid_idx = 0x0;
	for (i = 0; i < drvdata->numcidc; i++)
		config->ctxid_pid[i] = 0x0;

	config->ctxid_mask0 = 0x0;
	config->ctxid_mask1 = 0x0;

	config->vmid_idx = 0x0;
	for (i = 0; i < drvdata->numvmidc; i++)
		config->vmid_val[i] = 0x0;
	config->vmid_mask0 = 0x0;
	config->vmid_mask1 = 0x0;

	drvdata->trcid = drvdata->cpu + 1;

	spin_unlock(&drvdata->spinlock);

	return size;
}