#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  parent; } ;
struct TYPE_9__ {TYPE_2__ dev; TYPE_3__* algo_data; int /*<<< orphan*/  class; int /*<<< orphan*/  owner; int /*<<< orphan*/  name; } ;
struct TYPE_8__ {int udelay; int timeout; struct i740fb_par* data; int /*<<< orphan*/  getscl; int /*<<< orphan*/  getsda; int /*<<< orphan*/  setscl; int /*<<< orphan*/  setsda; } ;
struct i740fb_par {TYPE_4__ ddc_adapter; TYPE_3__ ddc_algo; } ;
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
struct fb_info {int /*<<< orphan*/  device; TYPE_1__ fix; struct i740fb_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_CLASS_DDC ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int i2c_bit_add_bus (TYPE_4__*) ; 
 int /*<<< orphan*/  i2c_set_adapdata (TYPE_4__*,struct i740fb_par*) ; 
 int /*<<< orphan*/  i740fb_ddc_getscl ; 
 int /*<<< orphan*/  i740fb_ddc_getsda ; 
 int /*<<< orphan*/  i740fb_ddc_setscl ; 
 int /*<<< orphan*/  i740fb_ddc_setsda ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int i740fb_setup_ddc_bus(struct fb_info *info)
{
	struct i740fb_par *par = info->par;

	strlcpy(par->ddc_adapter.name, info->fix.id,
		sizeof(par->ddc_adapter.name));
	par->ddc_adapter.owner		= THIS_MODULE;
	par->ddc_adapter.class		= I2C_CLASS_DDC;
	par->ddc_adapter.algo_data	= &par->ddc_algo;
	par->ddc_adapter.dev.parent	= info->device;
	par->ddc_algo.setsda		= i740fb_ddc_setsda;
	par->ddc_algo.setscl		= i740fb_ddc_setscl;
	par->ddc_algo.getsda		= i740fb_ddc_getsda;
	par->ddc_algo.getscl		= i740fb_ddc_getscl;
	par->ddc_algo.udelay		= 10;
	par->ddc_algo.timeout		= 20;
	par->ddc_algo.data		= par;

	i2c_set_adapdata(&par->ddc_adapter, par);

	return i2c_bit_add_bus(&par->ddc_adapter);
}