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
typedef  int /*<<< orphan*/  u8 ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int kstrtou8 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  slidebar_mode_set (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t store_slidebar_mode(struct device *dev,
				   struct device_attribute *attr,
				   const char *buf, size_t count)
{
	u8 mode;
	int error;

	error = kstrtou8(buf, 0, &mode);
	if (error)
		return error;

	slidebar_mode_set(mode);

	return count;
}