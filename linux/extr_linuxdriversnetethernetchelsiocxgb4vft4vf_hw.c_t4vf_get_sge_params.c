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
typedef  void* u32 ;
struct sge_params {unsigned int sge_host_page_size; unsigned int sge_egress_queues_per_page; unsigned int sge_ingress_queues_per_page; unsigned int sge_vf_hps; unsigned int sge_vf_eq_qpp; unsigned int sge_vf_iq_qpp; void* sge_congestion_control; void* sge_ingress_rx_threshold; void* sge_control2; void* sge_timer_value_4_and_5; void* sge_timer_value_2_and_3; void* sge_timer_value_0_and_1; void** sge_fl_buffer_size; void* sge_control; } ;
struct TYPE_2__ {int /*<<< orphan*/  chip; struct sge_params sge; } ;
struct adapter {int /*<<< orphan*/  pdev_dev; TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_PARAMS_MNEM_REG ; 
 int FW_PARAMS_MNEM_V (int /*<<< orphan*/ ) ; 
 int FW_PARAMS_PARAM_XYZ_V (int /*<<< orphan*/ ) ; 
 int FW_SUCCESS ; 
 unsigned int HOSTPAGESIZEPF0_M ; 
 unsigned int HOSTPAGESIZEPF0_S ; 
 unsigned int HOSTPAGESIZEPF1_S ; 
 unsigned int QUEUESPERPAGEPF0_M ; 
 unsigned int QUEUESPERPAGEPF0_S ; 
 unsigned int QUEUESPERPAGEPF1_S ; 
 int /*<<< orphan*/  SGE_CONM_CTRL_A ; 
 int /*<<< orphan*/  SGE_CONTROL2_A ; 
 int /*<<< orphan*/  SGE_CONTROL_A ; 
 int /*<<< orphan*/  SGE_EGRESS_QUEUES_PER_PAGE_VF_A ; 
 int /*<<< orphan*/  SGE_FL_BUFFER_SIZE0_A ; 
 int /*<<< orphan*/  SGE_FL_BUFFER_SIZE1_A ; 
 int /*<<< orphan*/  SGE_HOST_PAGE_SIZE_A ; 
 int /*<<< orphan*/  SGE_INGRESS_QUEUES_PER_PAGE_VF_A ; 
 int /*<<< orphan*/  SGE_INGRESS_RX_THRESHOLD_A ; 
 int /*<<< orphan*/  SGE_TIMER_VALUE_0_AND_1_A ; 
 int /*<<< orphan*/  SGE_TIMER_VALUE_2_AND_3_A ; 
 int /*<<< orphan*/  SGE_TIMER_VALUE_4_AND_5_A ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  is_t4 (int /*<<< orphan*/ ) ; 
 unsigned int t4vf_get_pf_from_vf (struct adapter*) ; 
 int t4vf_query_params (struct adapter*,int,void**,void**) ; 

int t4vf_get_sge_params(struct adapter *adapter)
{
	struct sge_params *sge_params = &adapter->params.sge;
	u32 params[7], vals[7];
	int v;

	params[0] = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_REG) |
		     FW_PARAMS_PARAM_XYZ_V(SGE_CONTROL_A));
	params[1] = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_REG) |
		     FW_PARAMS_PARAM_XYZ_V(SGE_HOST_PAGE_SIZE_A));
	params[2] = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_REG) |
		     FW_PARAMS_PARAM_XYZ_V(SGE_FL_BUFFER_SIZE0_A));
	params[3] = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_REG) |
		     FW_PARAMS_PARAM_XYZ_V(SGE_FL_BUFFER_SIZE1_A));
	params[4] = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_REG) |
		     FW_PARAMS_PARAM_XYZ_V(SGE_TIMER_VALUE_0_AND_1_A));
	params[5] = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_REG) |
		     FW_PARAMS_PARAM_XYZ_V(SGE_TIMER_VALUE_2_AND_3_A));
	params[6] = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_REG) |
		     FW_PARAMS_PARAM_XYZ_V(SGE_TIMER_VALUE_4_AND_5_A));
	v = t4vf_query_params(adapter, 7, params, vals);
	if (v)
		return v;
	sge_params->sge_control = vals[0];
	sge_params->sge_host_page_size = vals[1];
	sge_params->sge_fl_buffer_size[0] = vals[2];
	sge_params->sge_fl_buffer_size[1] = vals[3];
	sge_params->sge_timer_value_0_and_1 = vals[4];
	sge_params->sge_timer_value_2_and_3 = vals[5];
	sge_params->sge_timer_value_4_and_5 = vals[6];

	/* T4 uses a single control field to specify both the PCIe Padding and
	 * Packing Boundary.  T5 introduced the ability to specify these
	 * separately with the Padding Boundary in SGE_CONTROL and and Packing
	 * Boundary in SGE_CONTROL2.  So for T5 and later we need to grab
	 * SGE_CONTROL in order to determine how ingress packet data will be
	 * laid out in Packed Buffer Mode.  Unfortunately, older versions of
	 * the firmware won't let us retrieve SGE_CONTROL2 so if we get a
	 * failure grabbing it we throw an error since we can't figure out the
	 * right value.
	 */
	if (!is_t4(adapter->params.chip)) {
		params[0] = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_REG) |
			     FW_PARAMS_PARAM_XYZ_V(SGE_CONTROL2_A));
		v = t4vf_query_params(adapter, 1, params, vals);
		if (v != FW_SUCCESS) {
			dev_err(adapter->pdev_dev,
				"Unable to get SGE Control2; "
				"probably old firmware.\n");
			return v;
		}
		sge_params->sge_control2 = vals[0];
	}

	params[0] = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_REG) |
		     FW_PARAMS_PARAM_XYZ_V(SGE_INGRESS_RX_THRESHOLD_A));
	params[1] = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_REG) |
		     FW_PARAMS_PARAM_XYZ_V(SGE_CONM_CTRL_A));
	v = t4vf_query_params(adapter, 2, params, vals);
	if (v)
		return v;
	sge_params->sge_ingress_rx_threshold = vals[0];
	sge_params->sge_congestion_control = vals[1];

	/* For T5 and later we want to use the new BAR2 Doorbells.
	 * Unfortunately, older firmware didn't allow the this register to be
	 * read.
	 */
	if (!is_t4(adapter->params.chip)) {
		unsigned int pf, s_hps, s_qpp;

		params[0] = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_REG) |
			     FW_PARAMS_PARAM_XYZ_V(
				     SGE_EGRESS_QUEUES_PER_PAGE_VF_A));
		params[1] = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_REG) |
			     FW_PARAMS_PARAM_XYZ_V(
				     SGE_INGRESS_QUEUES_PER_PAGE_VF_A));
		v = t4vf_query_params(adapter, 2, params, vals);
		if (v != FW_SUCCESS) {
			dev_warn(adapter->pdev_dev,
				 "Unable to get VF SGE Queues/Page; "
				 "probably old firmware.\n");
			return v;
		}
		sge_params->sge_egress_queues_per_page = vals[0];
		sge_params->sge_ingress_queues_per_page = vals[1];

		/* We need the Queues/Page for our VF.  This is based on the
		 * PF from which we're instantiated and is indexed in the
		 * register we just read. Do it once here so other code in
		 * the driver can just use it.
		 */
		pf = t4vf_get_pf_from_vf(adapter);
		s_hps = (HOSTPAGESIZEPF0_S +
			 (HOSTPAGESIZEPF1_S - HOSTPAGESIZEPF0_S) * pf);
		sge_params->sge_vf_hps =
			((sge_params->sge_host_page_size >> s_hps)
			 & HOSTPAGESIZEPF0_M);

		s_qpp = (QUEUESPERPAGEPF0_S +
			 (QUEUESPERPAGEPF1_S - QUEUESPERPAGEPF0_S) * pf);
		sge_params->sge_vf_eq_qpp =
			((sge_params->sge_egress_queues_per_page >> s_qpp)
			 & QUEUESPERPAGEPF0_M);
		sge_params->sge_vf_iq_qpp =
			((sge_params->sge_ingress_queues_per_page >> s_qpp)
			 & QUEUESPERPAGEPF0_M);
	}

	return 0;
}