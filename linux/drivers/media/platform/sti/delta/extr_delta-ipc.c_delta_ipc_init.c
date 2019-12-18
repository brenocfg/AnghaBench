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
struct delta_dev {int /*<<< orphan*/  rpmsg_driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  delta_rpmsg_driver ; 
 int register_rpmsg_driver (int /*<<< orphan*/ *) ; 

int delta_ipc_init(struct delta_dev *delta)
{
	delta->rpmsg_driver = delta_rpmsg_driver;

	return register_rpmsg_driver(&delta->rpmsg_driver);
}