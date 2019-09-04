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
struct rc_dev {int /*<<< orphan*/  rc_map; int /*<<< orphan*/ * input_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ir_free_table (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rc_free_rx_device(struct rc_dev *dev)
{
	if (!dev)
		return;

	if (dev->input_dev) {
		input_unregister_device(dev->input_dev);
		dev->input_dev = NULL;
	}

	ir_free_table(&dev->rc_map);
}