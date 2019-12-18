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
struct i40e_pf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  i40e_control_rx_q (struct i40e_pf*,int,int) ; 
 int i40e_pf_rxq_wait (struct i40e_pf*,int,int) ; 

int i40e_control_wait_rx_q(struct i40e_pf *pf, int pf_q, bool enable)
{
	int ret = 0;

	i40e_control_rx_q(pf, pf_q, enable);

	/* wait for the change to finish */
	ret = i40e_pf_rxq_wait(pf, pf_q, enable);
	if (ret)
		return ret;

	return ret;
}