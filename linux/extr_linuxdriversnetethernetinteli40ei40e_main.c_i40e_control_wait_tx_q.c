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
struct i40e_pf {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,char*,int,char*) ; 
 int /*<<< orphan*/  i40e_control_tx_q (struct i40e_pf*,int,int) ; 
 int i40e_pf_txq_wait (struct i40e_pf*,int,int) ; 

int i40e_control_wait_tx_q(int seid, struct i40e_pf *pf, int pf_q,
			   bool is_xdp, bool enable)
{
	int ret;

	i40e_control_tx_q(pf, pf_q, enable);

	/* wait for the change to finish */
	ret = i40e_pf_txq_wait(pf, pf_q, enable);
	if (ret) {
		dev_info(&pf->pdev->dev,
			 "VSI seid %d %sTx ring %d %sable timeout\n",
			 seid, (is_xdp ? "XDP " : ""), pf_q,
			 (enable ? "en" : "dis"));
	}

	return ret;
}