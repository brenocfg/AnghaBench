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
struct sur40_state {int /*<<< orphan*/  dev; } ;
struct input_polled_dev {struct sur40_state* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void sur40_close(struct input_polled_dev *polldev)
{
	struct sur40_state *sur40 = polldev->private;

	dev_dbg(sur40->dev, "close\n");
	/*
	 * There is no known way to stop the device, so we simply
	 * stop polling.
	 */
}