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
struct hnae3_handle {int dummy; } ;
struct hclge_vport {int /*<<< orphan*/  alloc_tqps; } ;
struct ethtool_channels {int other_count; int max_other; int /*<<< orphan*/  combined_count; int /*<<< orphan*/  max_combined; } ;

/* Variables and functions */
 int /*<<< orphan*/  hclge_get_max_channels (struct hnae3_handle*) ; 
 struct hclge_vport* hclge_get_vport (struct hnae3_handle*) ; 

__attribute__((used)) static void hclge_get_channels(struct hnae3_handle *handle,
			       struct ethtool_channels *ch)
{
	struct hclge_vport *vport = hclge_get_vport(handle);

	ch->max_combined = hclge_get_max_channels(handle);
	ch->other_count = 1;
	ch->max_other = 1;
	ch->combined_count = vport->alloc_tqps;
}