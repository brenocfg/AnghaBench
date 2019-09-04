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
struct scoop_dev {scalar_t__ base; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct scoop_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  iowrite16 (unsigned short,scalar_t__) ; 

void write_scoop_reg(struct device *dev, unsigned short reg, unsigned short data)
{
	struct scoop_dev *sdev = dev_get_drvdata(dev);
	iowrite16(data, sdev->base + reg);
}