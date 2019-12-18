#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct radeonfb_info {TYPE_2__* i2c; } ;
struct TYPE_3__ {int /*<<< orphan*/  class; } ;
struct TYPE_4__ {int /*<<< orphan*/  ddc_reg; struct radeonfb_info* rinfo; TYPE_1__ adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_CRT2_DDC ; 
 int /*<<< orphan*/  GPIO_DVI_DDC ; 
 int /*<<< orphan*/  GPIO_MONID ; 
 int /*<<< orphan*/  GPIO_VGA_DDC ; 
 int /*<<< orphan*/  I2C_CLASS_HWMON ; 
 int /*<<< orphan*/  radeon_setup_i2c_bus (TYPE_2__*,char*) ; 

void radeon_create_i2c_busses(struct radeonfb_info *rinfo)
{
	rinfo->i2c[0].rinfo	= rinfo;
	rinfo->i2c[0].ddc_reg	= GPIO_MONID;
#ifndef CONFIG_PPC
	rinfo->i2c[0].adapter.class = I2C_CLASS_HWMON;
#endif
	radeon_setup_i2c_bus(&rinfo->i2c[0], "monid");

	rinfo->i2c[1].rinfo	= rinfo;
	rinfo->i2c[1].ddc_reg	= GPIO_DVI_DDC;
	radeon_setup_i2c_bus(&rinfo->i2c[1], "dvi");

	rinfo->i2c[2].rinfo	= rinfo;
	rinfo->i2c[2].ddc_reg	= GPIO_VGA_DDC;
	radeon_setup_i2c_bus(&rinfo->i2c[2], "vga");

	rinfo->i2c[3].rinfo	= rinfo;
	rinfo->i2c[3].ddc_reg	= GPIO_CRT2_DDC;
	radeon_setup_i2c_bus(&rinfo->i2c[3], "crt2");
}