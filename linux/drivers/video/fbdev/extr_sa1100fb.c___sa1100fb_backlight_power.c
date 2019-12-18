#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sa1100fb_info {TYPE_1__* inf; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* backlight_power ) (int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stub1 (int) ; 

__attribute__((used)) static inline void __sa1100fb_backlight_power(struct sa1100fb_info *fbi, int on)
{
	dev_dbg(fbi->dev, "backlight o%s\n", on ? "n" : "ff");

	if (fbi->inf->backlight_power)
		fbi->inf->backlight_power(on);
}