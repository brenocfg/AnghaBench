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
struct isp_device {scalar_t__ ref_count; int /*<<< orphan*/  isp_mutex; scalar_t__ has_context; } ;

/* Variables and functions */
 scalar_t__ isp_enable_clocks (struct isp_device*) ; 
 int /*<<< orphan*/  isp_enable_interrupts (struct isp_device*) ; 
 int /*<<< orphan*/  isp_restore_ctx (struct isp_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct isp_device *__omap3isp_get(struct isp_device *isp, bool irq)
{
	struct isp_device *__isp = isp;

	if (isp == NULL)
		return NULL;

	mutex_lock(&isp->isp_mutex);
	if (isp->ref_count > 0)
		goto out;

	if (isp_enable_clocks(isp) < 0) {
		__isp = NULL;
		goto out;
	}

	/* We don't want to restore context before saving it! */
	if (isp->has_context)
		isp_restore_ctx(isp);

	if (irq)
		isp_enable_interrupts(isp);

out:
	if (__isp != NULL)
		isp->ref_count++;
	mutex_unlock(&isp->isp_mutex);

	return __isp;
}