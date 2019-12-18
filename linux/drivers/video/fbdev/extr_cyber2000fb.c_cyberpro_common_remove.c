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
struct cfb_info {int /*<<< orphan*/  ddc_adapter; scalar_t__ ddc_registered; int /*<<< orphan*/  fb; } ;

/* Variables and functions */
 int /*<<< orphan*/  cyber2000fb_i2c_unregister (struct cfb_info*) ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_framebuffer (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cyberpro_common_remove(struct cfb_info *cfb)
{
	unregister_framebuffer(&cfb->fb);
#ifdef CONFIG_FB_CYBER2000_DDC
	if (cfb->ddc_registered)
		i2c_del_adapter(&cfb->ddc_adapter);
#endif
	cyber2000fb_i2c_unregister(cfb);
}