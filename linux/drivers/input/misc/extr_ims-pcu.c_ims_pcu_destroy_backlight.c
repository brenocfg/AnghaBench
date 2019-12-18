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
struct ims_pcu_backlight {int /*<<< orphan*/  cdev; } ;
struct ims_pcu {struct ims_pcu_backlight backlight; } ;

/* Variables and functions */
 int /*<<< orphan*/  led_classdev_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ims_pcu_destroy_backlight(struct ims_pcu *pcu)
{
	struct ims_pcu_backlight *backlight = &pcu->backlight;

	led_classdev_unregister(&backlight->cdev);
}