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
struct hnae3_handle {int dummy; } ;
struct hclge_vport {int /*<<< orphan*/  alloc_tqps; struct hclge_dev* back; } ;
struct hclge_dev {int /*<<< orphan*/  rss_size_max; } ;

/* Variables and functions */
 struct hclge_vport* hclge_get_vport (struct hnae3_handle*) ; 

__attribute__((used)) static void hclge_get_tqps_and_rss_info(struct hnae3_handle *handle,
					u16 *alloc_tqps, u16 *max_rss_size)
{
	struct hclge_vport *vport = hclge_get_vport(handle);
	struct hclge_dev *hdev = vport->back;

	*alloc_tqps = vport->alloc_tqps;
	*max_rss_size = hdev->rss_size_max;
}