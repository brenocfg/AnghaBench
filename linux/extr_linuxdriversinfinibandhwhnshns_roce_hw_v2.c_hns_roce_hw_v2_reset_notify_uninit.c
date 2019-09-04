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

/* Variables and functions */
 int /*<<< orphan*/  hns_roce_hw_v2_uninit_instance (struct hnae3_handle*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int hns_roce_hw_v2_reset_notify_uninit(struct hnae3_handle *handle)
{
	msleep(100);
	hns_roce_hw_v2_uninit_instance(handle, false);
	return 0;
}