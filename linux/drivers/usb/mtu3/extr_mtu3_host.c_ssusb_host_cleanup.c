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
struct ssusb_mtk {int /*<<< orphan*/  otg_switch; scalar_t__ is_host; } ;

/* Variables and functions */
 int /*<<< orphan*/  ssusb_host_disable (struct ssusb_mtk*,int) ; 
 int /*<<< orphan*/  ssusb_set_vbus (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ssusb_host_cleanup(struct ssusb_mtk *ssusb)
{
	if (ssusb->is_host)
		ssusb_set_vbus(&ssusb->otg_switch, 0);

	ssusb_host_disable(ssusb, false);
}