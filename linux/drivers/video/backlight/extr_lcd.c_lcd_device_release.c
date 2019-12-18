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
struct lcd_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct lcd_device*) ; 
 struct lcd_device* to_lcd_device (struct device*) ; 

__attribute__((used)) static void lcd_device_release(struct device *dev)
{
	struct lcd_device *ld = to_lcd_device(dev);
	kfree(ld);
}