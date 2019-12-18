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
struct hsi_msg {int /*<<< orphan*/  link; struct cs_hsi_iface* context; } ;
struct cs_hsi_iface {int /*<<< orphan*/  cmdqueue; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cs_release_cmd(struct hsi_msg *msg)
{
	struct cs_hsi_iface *hi = msg->context;

	list_add_tail(&msg->link, &hi->cmdqueue);
}