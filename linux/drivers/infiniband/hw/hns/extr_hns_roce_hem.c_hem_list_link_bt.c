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
typedef  int /*<<< orphan*/  u64 ;
struct hns_roce_dev {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void hem_list_link_bt(struct hns_roce_dev *hr_dev, void *base_addr,
			     u64 table_addr)
{
	*(u64 *)(base_addr) = table_addr;
}