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
struct rtllib_device {scalar_t__ mgmt_queue_head; scalar_t__ mgmt_queue_tail; } ;

/* Variables and functions */

__attribute__((used)) static void init_mgmt_queue(struct rtllib_device *ieee)
{
	ieee->mgmt_queue_tail = ieee->mgmt_queue_head = 0;
}