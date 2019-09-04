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
struct bh1770_chip {int lux_threshold_lo; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct bh1770_chip* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t bh1770_get_lux_thresh_below(struct device *dev,
				   struct device_attribute *attr, char *buf)
{
	struct bh1770_chip *chip =  dev_get_drvdata(dev);
	return sprintf(buf, "%d\n", chip->lux_threshold_lo);
}