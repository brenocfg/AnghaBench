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
struct platform_device {int dummy; } ;
struct goldfish_pipe_dev {scalar_t__ buffers; int /*<<< orphan*/  pipes; int /*<<< orphan*/  irq_tasklet; int /*<<< orphan*/  miscdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  misc_deregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void goldfish_pipe_device_deinit(struct platform_device *pdev,
					struct goldfish_pipe_dev *dev)
{
	misc_deregister(&dev->miscdev);
	tasklet_kill(&dev->irq_tasklet);
	kfree(dev->pipes);
	free_page((unsigned long)dev->buffers);
}