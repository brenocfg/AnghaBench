#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ssd1307fb_par {int /*<<< orphan*/  pwm; TYPE_2__* device_info; int /*<<< orphan*/  client; } ;
struct i2c_client {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  smem_len; int /*<<< orphan*/  smem_start; } ;
struct fb_info {TYPE_1__ fix; int /*<<< orphan*/  bl_dev; struct ssd1307fb_par* par; } ;
struct TYPE_4__ {scalar_t__ need_pwm; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSD1307FB_DISPLAY_OFF ; 
 int /*<<< orphan*/  __free_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __va (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  backlight_device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fb_deferred_io_cleanup (struct fb_info*) ; 
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 
 int /*<<< orphan*/  get_order (int /*<<< orphan*/ ) ; 
 struct fb_info* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  pwm_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwm_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssd1307fb_write_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_framebuffer (struct fb_info*) ; 

__attribute__((used)) static int ssd1307fb_remove(struct i2c_client *client)
{
	struct fb_info *info = i2c_get_clientdata(client);
	struct ssd1307fb_par *par = info->par;

	ssd1307fb_write_cmd(par->client, SSD1307FB_DISPLAY_OFF);

	backlight_device_unregister(info->bl_dev);

	unregister_framebuffer(info);
	if (par->device_info->need_pwm) {
		pwm_disable(par->pwm);
		pwm_put(par->pwm);
	}
	fb_deferred_io_cleanup(info);
	__free_pages(__va(info->fix.smem_start), get_order(info->fix.smem_len));
	framebuffer_release(info);

	return 0;
}