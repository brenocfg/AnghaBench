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
struct hnae3_handle {int dummy; } ;
struct TYPE_2__ {unsigned long hw_rst_done_cnt; } ;
struct hclgevf_dev {TYPE_1__ rst_stats; } ;

/* Variables and functions */
 struct hclgevf_dev* hclgevf_ae_get_hdev (struct hnae3_handle*) ; 

__attribute__((used)) static unsigned long hclgevf_ae_dev_reset_cnt(struct hnae3_handle *handle)
{
	struct hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);

	return hdev->rst_stats.hw_rst_done_cnt;
}