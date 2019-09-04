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
struct fmc_gpio {int dummy; } ;
struct fmc_device {TYPE_1__* op; } ;
struct TYPE_2__ {int (* gpio_config ) (struct fmc_device*,struct fmc_gpio*,int) ;} ;

/* Variables and functions */
 int EPERM ; 
 int stub1 (struct fmc_device*,struct fmc_gpio*,int) ; 

int fmc_gpio_config(struct fmc_device *fmc, struct fmc_gpio *gpio, int ngpio)
{
	if (fmc->op->gpio_config)
		return fmc->op->gpio_config(fmc, gpio, ngpio);
	return -EPERM;
}