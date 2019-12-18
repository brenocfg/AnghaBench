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
struct ntb_msi_devres {TYPE_1__* entry; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * write_msi_msg_data; int /*<<< orphan*/ * write_msi_msg; } ;

/* Variables and functions */

__attribute__((used)) static void ntbm_msi_callback_release(struct device *dev, void *res)
{
	struct ntb_msi_devres *dr = res;

	dr->entry->write_msi_msg = NULL;
	dr->entry->write_msi_msg_data = NULL;
}