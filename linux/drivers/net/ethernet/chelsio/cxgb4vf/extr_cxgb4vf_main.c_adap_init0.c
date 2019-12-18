#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct sge_params {int /*<<< orphan*/  sge_ingress_rx_threshold; int /*<<< orphan*/  sge_timer_value_4_and_5; int /*<<< orphan*/  sge_timer_value_2_and_3; int /*<<< orphan*/  sge_timer_value_0_and_1; } ;
struct sge {int /*<<< orphan*/ * counter_val; void** timer_val; } ;
struct TYPE_5__ {scalar_t__ pmask; scalar_t__ nvi; } ;
struct TYPE_4__ {int /*<<< orphan*/  mode; } ;
struct TYPE_6__ {TYPE_2__ vfres; TYPE_1__ rss; struct sge_params sge; } ;
struct adapter {int /*<<< orphan*/  flags; int /*<<< orphan*/  pdev_dev; TYPE_3__ params; struct sge sge; } ;

/* Variables and functions */
 int /*<<< orphan*/  CXGB4VF_FW_OK ; 
 int EINVAL ; 
 int /*<<< orphan*/  FW_PARAMS_MNEM_PFVF ; 
 int FW_PARAMS_MNEM_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FW_PARAMS_PARAM_PFVF_CPLFW4MSG_ENCAP ; 
 int FW_PARAMS_PARAM_X_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FW_RSS_GLB_CONFIG_CMD_MODE_BASICVIRTUAL ; 
 int /*<<< orphan*/  THRESHOLD_0_G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THRESHOLD_1_G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THRESHOLD_2_G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THRESHOLD_3_G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIMERVALUE0_G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIMERVALUE1_G (int /*<<< orphan*/ ) ; 
 void* core_ticks_to_us (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  size_nports_qsets (struct adapter*) ; 
 int t4vf_fw_reset (struct adapter*) ; 
 int t4vf_get_dev_params (struct adapter*) ; 
 int t4vf_get_rss_glb_config (struct adapter*) ; 
 int t4vf_get_sge_params (struct adapter*) ; 
 int t4vf_get_vfres (struct adapter*) ; 
 int t4vf_get_vpd_params (struct adapter*) ; 
 int /*<<< orphan*/  t4vf_set_params (struct adapter*,int,int*,int*) ; 
 int t4vf_sge_init (struct adapter*) ; 

__attribute__((used)) static int adap_init0(struct adapter *adapter)
{
	struct sge_params *sge_params = &adapter->params.sge;
	struct sge *s = &adapter->sge;
	int err;
	u32 param, val = 0;

	/*
	 * Some environments do not properly handle PCIE FLRs -- e.g. in Linux
	 * 2.6.31 and later we can't call pci_reset_function() in order to
	 * issue an FLR because of a self- deadlock on the device semaphore.
	 * Meanwhile, the OS infrastructure doesn't issue FLRs in all the
	 * cases where they're needed -- for instance, some versions of KVM
	 * fail to reset "Assigned Devices" when the VM reboots.  Therefore we
	 * use the firmware based reset in order to reset any per function
	 * state.
	 */
	err = t4vf_fw_reset(adapter);
	if (err < 0) {
		dev_err(adapter->pdev_dev, "FW reset failed: err=%d\n", err);
		return err;
	}

	/*
	 * Grab basic operational parameters.  These will predominantly have
	 * been set up by the Physical Function Driver or will be hard coded
	 * into the adapter.  We just have to live with them ...  Note that
	 * we _must_ get our VPD parameters before our SGE parameters because
	 * we need to know the adapter's core clock from the VPD in order to
	 * properly decode the SGE Timer Values.
	 */
	err = t4vf_get_dev_params(adapter);
	if (err) {
		dev_err(adapter->pdev_dev, "unable to retrieve adapter"
			" device parameters: err=%d\n", err);
		return err;
	}
	err = t4vf_get_vpd_params(adapter);
	if (err) {
		dev_err(adapter->pdev_dev, "unable to retrieve adapter"
			" VPD parameters: err=%d\n", err);
		return err;
	}
	err = t4vf_get_sge_params(adapter);
	if (err) {
		dev_err(adapter->pdev_dev, "unable to retrieve adapter"
			" SGE parameters: err=%d\n", err);
		return err;
	}
	err = t4vf_get_rss_glb_config(adapter);
	if (err) {
		dev_err(adapter->pdev_dev, "unable to retrieve adapter"
			" RSS parameters: err=%d\n", err);
		return err;
	}
	if (adapter->params.rss.mode !=
	    FW_RSS_GLB_CONFIG_CMD_MODE_BASICVIRTUAL) {
		dev_err(adapter->pdev_dev, "unable to operate with global RSS"
			" mode %d\n", adapter->params.rss.mode);
		return -EINVAL;
	}
	err = t4vf_sge_init(adapter);
	if (err) {
		dev_err(adapter->pdev_dev, "unable to use adapter parameters:"
			" err=%d\n", err);
		return err;
	}

	/* If we're running on newer firmware, let it know that we're
	 * prepared to deal with encapsulated CPL messages.  Older
	 * firmware won't understand this and we'll just get
	 * unencapsulated messages ...
	 */
	param = FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_PFVF) |
		FW_PARAMS_PARAM_X_V(FW_PARAMS_PARAM_PFVF_CPLFW4MSG_ENCAP);
	val = 1;
	(void) t4vf_set_params(adapter, 1, &param, &val);

	/*
	 * Retrieve our RX interrupt holdoff timer values and counter
	 * threshold values from the SGE parameters.
	 */
	s->timer_val[0] = core_ticks_to_us(adapter,
		TIMERVALUE0_G(sge_params->sge_timer_value_0_and_1));
	s->timer_val[1] = core_ticks_to_us(adapter,
		TIMERVALUE1_G(sge_params->sge_timer_value_0_and_1));
	s->timer_val[2] = core_ticks_to_us(adapter,
		TIMERVALUE0_G(sge_params->sge_timer_value_2_and_3));
	s->timer_val[3] = core_ticks_to_us(adapter,
		TIMERVALUE1_G(sge_params->sge_timer_value_2_and_3));
	s->timer_val[4] = core_ticks_to_us(adapter,
		TIMERVALUE0_G(sge_params->sge_timer_value_4_and_5));
	s->timer_val[5] = core_ticks_to_us(adapter,
		TIMERVALUE1_G(sge_params->sge_timer_value_4_and_5));

	s->counter_val[0] = THRESHOLD_0_G(sge_params->sge_ingress_rx_threshold);
	s->counter_val[1] = THRESHOLD_1_G(sge_params->sge_ingress_rx_threshold);
	s->counter_val[2] = THRESHOLD_2_G(sge_params->sge_ingress_rx_threshold);
	s->counter_val[3] = THRESHOLD_3_G(sge_params->sge_ingress_rx_threshold);

	/*
	 * Grab our Virtual Interface resource allocation, extract the
	 * features that we're interested in and do a bit of sanity testing on
	 * what we discover.
	 */
	err = t4vf_get_vfres(adapter);
	if (err) {
		dev_err(adapter->pdev_dev, "unable to get virtual interface"
			" resources: err=%d\n", err);
		return err;
	}

	/* Check for various parameter sanity issues */
	if (adapter->params.vfres.pmask == 0) {
		dev_err(adapter->pdev_dev, "no port access configured\n"
			"usable!\n");
		return -EINVAL;
	}
	if (adapter->params.vfres.nvi == 0) {
		dev_err(adapter->pdev_dev, "no virtual interfaces configured/"
			"usable!\n");
		return -EINVAL;
	}

	/* Initialize nports and max_ethqsets now that we have our Virtual
	 * Function Resources.
	 */
	size_nports_qsets(adapter);

	adapter->flags |= CXGB4VF_FW_OK;
	return 0;
}