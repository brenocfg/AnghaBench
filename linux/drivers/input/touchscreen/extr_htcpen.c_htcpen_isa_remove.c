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
struct input_dev {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HTCPEN_IRQ ; 
 int /*<<< orphan*/  HTCPEN_PORT_INDEX ; 
 int /*<<< orphan*/  HTCPEN_PORT_INIT ; 
 int /*<<< orphan*/  HTCPEN_PORT_IRQ_CLEAR ; 
 struct input_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct input_dev*) ; 
 int /*<<< orphan*/  input_unregister_device (struct input_dev*) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int htcpen_isa_remove(struct device *dev, unsigned int id)
{
	struct input_dev *htcpen_dev = dev_get_drvdata(dev);

	input_unregister_device(htcpen_dev);

	free_irq(HTCPEN_IRQ, htcpen_dev);

	release_region(HTCPEN_PORT_INDEX, 2);
	release_region(HTCPEN_PORT_INIT, 1);
	release_region(HTCPEN_PORT_IRQ_CLEAR, 1);

	return 0;
}