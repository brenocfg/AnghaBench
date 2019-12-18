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
typedef  int /*<<< orphan*/  u8 ;
struct device {int dummy; } ;
struct adt7x10_data {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* write_byte ) (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 struct adt7x10_data* dev_get_drvdata (struct device*) ; 
 int stub1 (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adt7x10_write_byte(struct device *dev, u8 reg, u8 data)
{
	struct adt7x10_data *d = dev_get_drvdata(dev);
	return d->ops->write_byte(dev, reg, data);
}