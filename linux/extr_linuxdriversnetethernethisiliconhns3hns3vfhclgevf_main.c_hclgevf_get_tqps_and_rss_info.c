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
typedef  scalar_t__ u16 ;
struct hnae3_handle {int dummy; } ;
struct hclgevf_dev {scalar_t__ rss_size_max; } ;

/* Variables and functions */
 struct hclgevf_dev* hclgevf_ae_get_hdev (struct hnae3_handle*) ; 

__attribute__((used)) static void hclgevf_get_tqps_and_rss_info(struct hnae3_handle *handle,
					  u16 *free_tqps, u16 *max_rss_size)
{
	struct hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);

	*free_tqps = 0;
	*max_rss_size = hdev->rss_size_max;
}