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
typedef  int /*<<< orphan*/  u64 ;
struct hnae3_handle {int dummy; } ;
struct hclge_vport {struct hclge_dev* back; } ;
struct TYPE_2__ {int /*<<< orphan*/  mac_stats; } ;
struct hclge_dev {TYPE_1__ hw_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_mac_stats_string ; 
 int /*<<< orphan*/ * hclge_comm_get_stats (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct hclge_vport* hclge_get_vport (struct hnae3_handle*) ; 
 int /*<<< orphan*/ * hclge_tqps_get_stats (struct hnae3_handle*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hclge_get_stats(struct hnae3_handle *handle, u64 *data)
{
	struct hclge_vport *vport = hclge_get_vport(handle);
	struct hclge_dev *hdev = vport->back;
	u64 *p;

	p = hclge_comm_get_stats(&hdev->hw_stats.mac_stats, g_mac_stats_string,
				 ARRAY_SIZE(g_mac_stats_string), data);
	p = hclge_tqps_get_stats(handle, p);
}