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
struct imx_i2c_struct {TYPE_1__* hwdata; } ;
struct TYPE_2__ {scalar_t__ devtype; } ;

/* Variables and functions */
 scalar_t__ IMX1_I2C ; 

__attribute__((used)) static inline int is_imx1_i2c(struct imx_i2c_struct *i2c_imx)
{
	return i2c_imx->hwdata->devtype == IMX1_I2C;
}