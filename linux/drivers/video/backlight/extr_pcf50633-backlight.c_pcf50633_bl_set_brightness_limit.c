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
struct pcf50633_bl {unsigned int brightness_limit; int /*<<< orphan*/  bl; } ;
struct pcf50633 {int /*<<< orphan*/  bl_pdev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  backlight_update_status (int /*<<< orphan*/ ) ; 
 struct pcf50633_bl* platform_get_drvdata (int /*<<< orphan*/ ) ; 

int pcf50633_bl_set_brightness_limit(struct pcf50633 *pcf, unsigned int limit)
{
	struct pcf50633_bl *pcf_bl = platform_get_drvdata(pcf->bl_pdev);

	if (!pcf_bl)
		return -ENODEV;

	pcf_bl->brightness_limit = limit & 0x3f;
	backlight_update_status(pcf_bl->bl);

	return 0;
}