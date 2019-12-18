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
typedef  int u32 ;
struct s3c_fb {int output_on; int /*<<< orphan*/  dev; scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ VIDCON0 ; 
 int VIDCON0_ENVID ; 
 int VIDCON0_ENVID_F ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void s3c_fb_enable(struct s3c_fb *sfb, int enable)
{
	u32 vidcon0 = readl(sfb->regs + VIDCON0);

	if (enable && !sfb->output_on)
		pm_runtime_get_sync(sfb->dev);

	if (enable) {
		vidcon0 |= VIDCON0_ENVID | VIDCON0_ENVID_F;
	} else {
		/* see the note in the framebuffer datasheet about
		 * why you cannot take both of these bits down at the
		 * same time. */

		if (vidcon0 & VIDCON0_ENVID) {
			vidcon0 |= VIDCON0_ENVID;
			vidcon0 &= ~VIDCON0_ENVID_F;
		}
	}

	writel(vidcon0, sfb->regs + VIDCON0);

	if (!enable && sfb->output_on)
		pm_runtime_put_sync(sfb->dev);

	sfb->output_on = enable;
}