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
struct i40evf_adapter {int aq_required; } ;

/* Variables and functions */
 int I40EVF_FLAG_AQ_SET_RSS_KEY ; 
 int I40EVF_FLAG_AQ_SET_RSS_LUT ; 
 scalar_t__ RSS_AQ (struct i40evf_adapter*) ; 
 scalar_t__ RSS_PF (struct i40evf_adapter*) ; 
 int i40evf_config_rss_aq (struct i40evf_adapter*) ; 
 int i40evf_config_rss_reg (struct i40evf_adapter*) ; 

int i40evf_config_rss(struct i40evf_adapter *adapter)
{

	if (RSS_PF(adapter)) {
		adapter->aq_required |= I40EVF_FLAG_AQ_SET_RSS_LUT |
					I40EVF_FLAG_AQ_SET_RSS_KEY;
		return 0;
	} else if (RSS_AQ(adapter)) {
		return i40evf_config_rss_aq(adapter);
	} else {
		return i40evf_config_rss_reg(adapter);
	}
}