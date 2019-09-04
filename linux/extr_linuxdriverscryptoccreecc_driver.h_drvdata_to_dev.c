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
struct device {int dummy; } ;
struct cc_drvdata {TYPE_1__* plat_dev; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */

__attribute__((used)) static inline struct device *drvdata_to_dev(struct cc_drvdata *drvdata)
{
	return &drvdata->plat_dev->dev;
}