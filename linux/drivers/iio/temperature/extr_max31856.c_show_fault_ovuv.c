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
 int /*<<< orphan*/  MAX31856_FAULT_OVUV ; 
 int /*<<< orphan*/  show_fault (struct device*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ssize_t show_fault_ovuv(struct device *dev,
			       struct device_attribute *attr,
			       char *buf)
{
	return show_fault(dev, MAX31856_FAULT_OVUV, buf);
}