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
struct fb_info {int /*<<< orphan*/  fbcon_par; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int* con2fb_map ; 
 int /*<<< orphan*/  console_lock () ; 
 int /*<<< orphan*/  console_unlock () ; 
 int /*<<< orphan*/  fbcon_add_cursor_timer (struct fb_info*) ; 
 int fbcon_cursor_noblink ; 
 int /*<<< orphan*/  fbcon_del_cursor_timer (struct fb_info*) ; 
 size_t fg_console ; 
 struct fb_info** registered_fb ; 
 int simple_strtoul (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t store_cursor_blink(struct device *device,
				  struct device_attribute *attr,
				  const char *buf, size_t count)
{
	struct fb_info *info;
	int blink, idx;
	char **last = NULL;

	console_lock();
	idx = con2fb_map[fg_console];

	if (idx == -1 || registered_fb[idx] == NULL)
		goto err;

	info = registered_fb[idx];

	if (!info->fbcon_par)
		goto err;

	blink = simple_strtoul(buf, last, 0);

	if (blink) {
		fbcon_cursor_noblink = 0;
		fbcon_add_cursor_timer(info);
	} else {
		fbcon_cursor_noblink = 1;
		fbcon_del_cursor_timer(info);
	}

err:
	console_unlock();
	return count;
}