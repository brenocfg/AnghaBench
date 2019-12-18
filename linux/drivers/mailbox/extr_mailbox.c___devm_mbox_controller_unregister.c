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
struct mbox_controller {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mbox_controller_unregister (struct mbox_controller*) ; 

__attribute__((used)) static void __devm_mbox_controller_unregister(struct device *dev, void *res)
{
	struct mbox_controller **mbox = res;

	mbox_controller_unregister(*mbox);
}