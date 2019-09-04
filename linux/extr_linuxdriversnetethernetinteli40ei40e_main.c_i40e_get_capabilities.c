#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_11__ {scalar_t__ num_vfs; scalar_t__ num_vsis; scalar_t__ fcoe; int /*<<< orphan*/  num_tx_qp; int /*<<< orphan*/  fd_filters_best_effort; int /*<<< orphan*/  fd_filters_guaranteed; int /*<<< orphan*/  num_msix_vectors_vf; int /*<<< orphan*/  num_msix_vectors; } ;
struct TYPE_9__ {scalar_t__ switch_mode; scalar_t__ valid_functions; scalar_t__ sr_iov_1_1; scalar_t__ num_vfs; int /*<<< orphan*/  num_tx_qp; int /*<<< orphan*/  num_rx_qp; int /*<<< orphan*/  num_vsis; } ;
struct TYPE_8__ {scalar_t__ asq_last_status; } ;
struct TYPE_12__ {int debug_mask; scalar_t__ revision_id; TYPE_4__ func_caps; TYPE_2__ dev_caps; int /*<<< orphan*/  pf_id; TYPE_1__ aq; } ;
struct i40e_pf {TYPE_5__ hw; TYPE_3__* pdev; } ;
struct i40e_aqc_list_capabilities_element_resp {int dummy; } ;
typedef  enum i40e_admin_queue_opc { ____Placeholder_i40e_admin_queue_opc } i40e_admin_queue_opc ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ I40E_AQ_RC_ENOMEM ; 
 scalar_t__ I40E_AQ_RC_OK ; 
 int I40E_DEBUG_USER ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,scalar_t__,scalar_t__,...) ; 
 int i40e_aq_discover_capabilities (TYPE_5__*,struct i40e_aqc_list_capabilities_element_resp*,int,int*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ i40e_aq_str (TYPE_5__*,scalar_t__) ; 
 int i40e_aqc_opc_list_dev_capabilities ; 
 int i40e_aqc_opc_list_func_capabilities ; 
 scalar_t__ i40e_stat_str (TYPE_5__*,int) ; 
 int /*<<< orphan*/  kfree (struct i40e_aqc_list_capabilities_element_resp*) ; 
 struct i40e_aqc_list_capabilities_element_resp* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i40e_get_capabilities(struct i40e_pf *pf,
				 enum i40e_admin_queue_opc list_type)
{
	struct i40e_aqc_list_capabilities_element_resp *cap_buf;
	u16 data_size;
	int buf_len;
	int err;

	buf_len = 40 * sizeof(struct i40e_aqc_list_capabilities_element_resp);
	do {
		cap_buf = kzalloc(buf_len, GFP_KERNEL);
		if (!cap_buf)
			return -ENOMEM;

		/* this loads the data into the hw struct for us */
		err = i40e_aq_discover_capabilities(&pf->hw, cap_buf, buf_len,
						    &data_size, list_type,
						    NULL);
		/* data loaded, buffer no longer needed */
		kfree(cap_buf);

		if (pf->hw.aq.asq_last_status == I40E_AQ_RC_ENOMEM) {
			/* retry with a larger buffer */
			buf_len = data_size;
		} else if (pf->hw.aq.asq_last_status != I40E_AQ_RC_OK) {
			dev_info(&pf->pdev->dev,
				 "capability discovery failed, err %s aq_err %s\n",
				 i40e_stat_str(&pf->hw, err),
				 i40e_aq_str(&pf->hw,
					     pf->hw.aq.asq_last_status));
			return -ENODEV;
		}
	} while (err);

	if (pf->hw.debug_mask & I40E_DEBUG_USER) {
		if (list_type == i40e_aqc_opc_list_func_capabilities) {
			dev_info(&pf->pdev->dev,
				 "pf=%d, num_vfs=%d, msix_pf=%d, msix_vf=%d, fd_g=%d, fd_b=%d, pf_max_q=%d num_vsi=%d\n",
				 pf->hw.pf_id, pf->hw.func_caps.num_vfs,
				 pf->hw.func_caps.num_msix_vectors,
				 pf->hw.func_caps.num_msix_vectors_vf,
				 pf->hw.func_caps.fd_filters_guaranteed,
				 pf->hw.func_caps.fd_filters_best_effort,
				 pf->hw.func_caps.num_tx_qp,
				 pf->hw.func_caps.num_vsis);
		} else if (list_type == i40e_aqc_opc_list_dev_capabilities) {
			dev_info(&pf->pdev->dev,
				 "switch_mode=0x%04x, function_valid=0x%08x\n",
				 pf->hw.dev_caps.switch_mode,
				 pf->hw.dev_caps.valid_functions);
			dev_info(&pf->pdev->dev,
				 "SR-IOV=%d, num_vfs for all function=%u\n",
				 pf->hw.dev_caps.sr_iov_1_1,
				 pf->hw.dev_caps.num_vfs);
			dev_info(&pf->pdev->dev,
				 "num_vsis=%u, num_rx:%u, num_tx=%u\n",
				 pf->hw.dev_caps.num_vsis,
				 pf->hw.dev_caps.num_rx_qp,
				 pf->hw.dev_caps.num_tx_qp);
		}
	}
	if (list_type == i40e_aqc_opc_list_func_capabilities) {
#define DEF_NUM_VSI (1 + (pf->hw.func_caps.fcoe ? 1 : 0) \
		       + pf->hw.func_caps.num_vfs)
		if (pf->hw.revision_id == 0 &&
		    pf->hw.func_caps.num_vsis < DEF_NUM_VSI) {
			dev_info(&pf->pdev->dev,
				 "got num_vsis %d, setting num_vsis to %d\n",
				 pf->hw.func_caps.num_vsis, DEF_NUM_VSI);
			pf->hw.func_caps.num_vsis = DEF_NUM_VSI;
		}
	}
	return 0;
}