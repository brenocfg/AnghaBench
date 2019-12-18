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
struct gb_control {struct gb_control* product_string; struct gb_control* vendor_string; int /*<<< orphan*/  connection; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gb_connection_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct gb_control*) ; 
 struct gb_control* to_gb_control (struct device*) ; 

__attribute__((used)) static void gb_control_release(struct device *dev)
{
	struct gb_control *control = to_gb_control(dev);

	gb_connection_destroy(control->connection);

	kfree(control->vendor_string);
	kfree(control->product_string);

	kfree(control);
}