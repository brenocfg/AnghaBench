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
struct iavf_adapter {int aq_required; } ;

/* Variables and functions */
 int IAVF_FLAG_AQ_SET_RSS_KEY ; 
 int IAVF_FLAG_AQ_SET_RSS_LUT ; 
 scalar_t__ RSS_AQ (struct iavf_adapter*) ; 
 scalar_t__ RSS_PF (struct iavf_adapter*) ; 
 int iavf_config_rss_aq (struct iavf_adapter*) ; 
 int iavf_config_rss_reg (struct iavf_adapter*) ; 

int iavf_config_rss(struct iavf_adapter *adapter)
{

	if (RSS_PF(adapter)) {
		adapter->aq_required |= IAVF_FLAG_AQ_SET_RSS_LUT |
					IAVF_FLAG_AQ_SET_RSS_KEY;
		return 0;
	} else if (RSS_AQ(adapter)) {
		return iavf_config_rss_aq(adapter);
	} else {
		return iavf_config_rss_reg(adapter);
	}
}