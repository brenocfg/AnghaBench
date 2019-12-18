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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  LCD_LINE1_OFFSET ; 
 int /*<<< orphan*/  LCD_LINE1_SIZE ; 
 int /*<<< orphan*/  store_line (struct device*,char const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t store_line1(struct device *dev, struct device_attribute *attr,
				const char *buf, size_t count)
{
	return store_line(dev, buf, count, LCD_LINE1_OFFSET, LCD_LINE1_SIZE);
}