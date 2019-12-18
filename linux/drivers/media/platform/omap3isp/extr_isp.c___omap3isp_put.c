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
struct isp_device {scalar_t__ ref_count; int has_context; int /*<<< orphan*/  isp_mutex; scalar_t__ stop_failure; int /*<<< orphan*/  crashed; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  isp_disable_clocks (struct isp_device*) ; 
 int /*<<< orphan*/  isp_disable_interrupts (struct isp_device*) ; 
 int /*<<< orphan*/  isp_reset (struct isp_device*) ; 
 int /*<<< orphan*/  isp_save_ctx (struct isp_device*) ; 
 int /*<<< orphan*/  media_entity_enum_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __omap3isp_put(struct isp_device *isp, bool save_ctx)
{
	if (isp == NULL)
		return;

	mutex_lock(&isp->isp_mutex);
	BUG_ON(isp->ref_count == 0);
	if (--isp->ref_count == 0) {
		isp_disable_interrupts(isp);
		if (save_ctx) {
			isp_save_ctx(isp);
			isp->has_context = 1;
		}
		/* Reset the ISP if an entity has failed to stop. This is the
		 * only way to recover from such conditions.
		 */
		if (!media_entity_enum_empty(&isp->crashed) ||
		    isp->stop_failure)
			isp_reset(isp);
		isp_disable_clocks(isp);
	}
	mutex_unlock(&isp->isp_mutex);
}