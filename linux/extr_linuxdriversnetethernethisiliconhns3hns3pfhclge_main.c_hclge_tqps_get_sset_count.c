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
struct hnae3_knic_private_info {int num_tqps; } ;
struct hnae3_handle {struct hnae3_knic_private_info kinfo; } ;

/* Variables and functions */

__attribute__((used)) static int hclge_tqps_get_sset_count(struct hnae3_handle *handle, int stringset)
{
	struct hnae3_knic_private_info *kinfo = &handle->kinfo;

	return kinfo->num_tqps * (2);
}