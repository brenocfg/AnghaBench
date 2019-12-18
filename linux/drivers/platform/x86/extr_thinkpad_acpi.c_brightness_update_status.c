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
struct TYPE_2__ {scalar_t__ fb_blank; scalar_t__ power; unsigned int brightness; } ;
struct backlight_device {TYPE_1__ props; } ;

/* Variables and functions */
 scalar_t__ FB_BLANK_UNBLANK ; 
 int /*<<< orphan*/  TPACPI_DBG_BRGHT ; 
 int brightness_set (unsigned int) ; 
 int /*<<< orphan*/  dbg_printk (int /*<<< orphan*/ ,char*,unsigned int) ; 

__attribute__((used)) static int brightness_update_status(struct backlight_device *bd)
{
	unsigned int level =
		(bd->props.fb_blank == FB_BLANK_UNBLANK &&
		 bd->props.power == FB_BLANK_UNBLANK) ?
				bd->props.brightness : 0;

	dbg_printk(TPACPI_DBG_BRGHT,
			"backlight: attempt to set level to %d\n",
			level);

	/* it is the backlight class's job (caller) to handle
	 * EINTR and other errors properly */
	return brightness_set(level);
}