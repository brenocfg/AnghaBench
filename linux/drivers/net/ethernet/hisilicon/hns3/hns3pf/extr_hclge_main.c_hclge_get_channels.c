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
struct ethtool_channels {int other_count; int max_other; int /*<<< orphan*/  combined_count; int /*<<< orphan*/  max_combined; } ;

/* Variables and functions */
 int /*<<< orphan*/  hclge_get_max_channels (struct hnae3_handle*) ; 

__attribute__((used)) static void hclge_get_channels(struct hnae3_handle *handle,
			       struct ethtool_channels *ch)
{
	ch->max_combined = hclge_get_max_channels(handle);
	ch->other_count = 1;
	ch->max_other = 1;
	ch->combined_count = handle->kinfo.rss_size;
}