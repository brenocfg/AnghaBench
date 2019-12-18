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
typedef  int /*<<< orphan*/  u16 ;
struct iavf_hw {int dummy; } ;
struct iavf_aqc_get_set_rss_key_data {int dummy; } ;
typedef  enum iavf_status { ____Placeholder_iavf_status } iavf_status ;

/* Variables and functions */
 int iavf_aq_get_set_rss_key (struct iavf_hw*,int /*<<< orphan*/ ,struct iavf_aqc_get_set_rss_key_data*,int) ; 

enum iavf_status iavf_aq_get_rss_key(struct iavf_hw *hw, u16 vsi_id,
				     struct iavf_aqc_get_set_rss_key_data *key)
{
	return iavf_aq_get_set_rss_key(hw, vsi_id, key, false);
}