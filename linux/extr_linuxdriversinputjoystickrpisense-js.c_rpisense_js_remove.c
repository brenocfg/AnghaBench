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
struct rpisense_js {int /*<<< orphan*/  keys_dev; } ;
struct platform_device {int dummy; } ;
struct TYPE_2__ {struct rpisense_js joystick; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_free_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 TYPE_1__* rpisense ; 

__attribute__((used)) static int rpisense_js_remove(struct platform_device *pdev)
{
	struct rpisense_js *rpisense_js = &rpisense->joystick;

	input_unregister_device(rpisense_js->keys_dev);
	input_free_device(rpisense_js->keys_dev);
	return 0;
}