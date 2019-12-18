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
struct ssusb_mtk {scalar_t__ uwk_en; } ;

/* Variables and functions */
 int /*<<< orphan*/  ssusb_wakeup_ip_sleep_set (struct ssusb_mtk*,int) ; 

void ssusb_wakeup_set(struct ssusb_mtk *ssusb, bool enable)
{
	if (ssusb->uwk_en)
		ssusb_wakeup_ip_sleep_set(ssusb, enable);
}