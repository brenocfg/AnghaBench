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
struct mic_irq {int dummy; } ;
struct mbus_device {int dummy; } ;
typedef  int /*<<< orphan*/  irq_handler_t ;

/* Variables and functions */
 int /*<<< orphan*/  MIC_INTR_DMA ; 
 int /*<<< orphan*/  mbdev_to_mdev (struct mbus_device*) ; 
 struct mic_irq* mic_request_threaded_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,void*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mic_irq *
_mic_request_threaded_irq(struct mbus_device *mbdev,
			  irq_handler_t handler, irq_handler_t thread_fn,
			  const char *name, void *data, int intr_src)
{
	return mic_request_threaded_irq(mbdev_to_mdev(mbdev), handler,
					thread_fn, name, data,
					intr_src, MIC_INTR_DMA);
}