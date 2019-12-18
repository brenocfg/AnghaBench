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
struct hclgevf_dev {int dummy; } ;

/* Variables and functions */
 int hclgevf_get_pf_media_type (struct hclgevf_dev*) ; 
 int hclgevf_get_port_base_vlan_filter_state (struct hclgevf_dev*) ; 
 int hclgevf_get_queue_depth (struct hclgevf_dev*) ; 
 int hclgevf_get_queue_info (struct hclgevf_dev*) ; 
 int hclgevf_get_tc_info (struct hclgevf_dev*) ; 

__attribute__((used)) static int hclgevf_configure(struct hclgevf_dev *hdev)
{
	int ret;

	/* get current port based vlan state from PF */
	ret = hclgevf_get_port_base_vlan_filter_state(hdev);
	if (ret)
		return ret;

	/* get queue configuration from PF */
	ret = hclgevf_get_queue_info(hdev);
	if (ret)
		return ret;

	/* get queue depth info from PF */
	ret = hclgevf_get_queue_depth(hdev);
	if (ret)
		return ret;

	ret = hclgevf_get_pf_media_type(hdev);
	if (ret)
		return ret;

	/* get tc configuration from PF */
	return hclgevf_get_tc_info(hdev);
}