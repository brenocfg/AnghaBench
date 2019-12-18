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
struct tps6586x {int version; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct tps6586x* dev_get_drvdata (struct device*) ; 

int tps6586x_get_version(struct device *dev)
{
	struct tps6586x *tps6586x = dev_get_drvdata(dev);

	return tps6586x->version;
}