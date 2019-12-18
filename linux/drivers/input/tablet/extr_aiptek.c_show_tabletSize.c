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
struct aiptek {int /*<<< orphan*/  inputdev; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct aiptek* dev_get_drvdata (struct device*) ; 
 int input_abs_get_max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int,int) ; 

__attribute__((used)) static ssize_t show_tabletSize(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct aiptek *aiptek = dev_get_drvdata(dev);

	return snprintf(buf, PAGE_SIZE, "%dx%d\n",
			input_abs_get_max(aiptek->inputdev, ABS_X) + 1,
			input_abs_get_max(aiptek->inputdev, ABS_Y) + 1);
}