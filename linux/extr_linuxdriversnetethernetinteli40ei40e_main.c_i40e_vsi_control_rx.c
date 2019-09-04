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
struct i40e_vsi {int base_queue; int num_queue_pairs; int /*<<< orphan*/  seid; struct i40e_pf* back; } ;
struct i40e_pf {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,char*) ; 
 int i40e_control_wait_rx_q (struct i40e_pf*,int,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static int i40e_vsi_control_rx(struct i40e_vsi *vsi, bool enable)
{
	struct i40e_pf *pf = vsi->back;
	int i, pf_q, ret = 0;

	pf_q = vsi->base_queue;
	for (i = 0; i < vsi->num_queue_pairs; i++, pf_q++) {
		ret = i40e_control_wait_rx_q(pf, pf_q, enable);
		if (ret) {
			dev_info(&pf->pdev->dev,
				 "VSI seid %d Rx ring %d %sable timeout\n",
				 vsi->seid, pf_q, (enable ? "en" : "dis"));
			break;
		}
	}

	/* Due to HW errata, on Rx disable only, the register can indicate done
	 * before it really is. Needs 50ms to be sure
	 */
	if (!enable)
		mdelay(50);

	return ret;
}