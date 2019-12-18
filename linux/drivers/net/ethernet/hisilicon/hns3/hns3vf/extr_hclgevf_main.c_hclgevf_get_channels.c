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
struct TYPE_2__ {int /*<<< orphan*/  rss_size; } ;
struct hnae3_handle {TYPE_1__ kinfo; } ;
struct hclgevf_dev {int dummy; } ;
struct ethtool_channels {int /*<<< orphan*/  combined_count; scalar_t__ max_other; scalar_t__ other_count; int /*<<< orphan*/  max_combined; } ;

/* Variables and functions */
 struct hclgevf_dev* hclgevf_ae_get_hdev (struct hnae3_handle*) ; 
 int /*<<< orphan*/  hclgevf_get_max_channels (struct hclgevf_dev*) ; 

__attribute__((used)) static void hclgevf_get_channels(struct hnae3_handle *handle,
				 struct ethtool_channels *ch)
{
	struct hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);

	ch->max_combined = hclgevf_get_max_channels(hdev);
	ch->other_count = 0;
	ch->max_other = 0;
	ch->combined_count = handle->kinfo.rss_size;
}