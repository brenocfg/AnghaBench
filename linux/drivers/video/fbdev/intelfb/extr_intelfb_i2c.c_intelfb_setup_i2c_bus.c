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
typedef  int /*<<< orphan*/  u32 ;
struct intelfb_info {TYPE_2__* pdev; } ;
struct TYPE_6__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_9__ {int class; TYPE_1__ dev; TYPE_3__* algo_data; int /*<<< orphan*/  owner; int /*<<< orphan*/  name; } ;
struct TYPE_8__ {int udelay; int timeout; struct intelfb_i2c_chan* data; int /*<<< orphan*/  getscl; int /*<<< orphan*/  getsda; int /*<<< orphan*/  (* setscl ) (struct intelfb_i2c_chan*,int) ;int /*<<< orphan*/  (* setsda ) (struct intelfb_i2c_chan*,int) ;} ;
struct intelfb_i2c_chan {TYPE_4__ adapter; TYPE_3__ algo; struct intelfb_info* dinfo; int /*<<< orphan*/  reg; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_MSG (char*,char const*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  WRN_MSG (char*,char const*) ; 
 int i2c_bit_add_bus (TYPE_4__*) ; 
 int /*<<< orphan*/  i2c_set_adapdata (TYPE_4__*,struct intelfb_i2c_chan*) ; 
 int /*<<< orphan*/  intelfb_gpio_getscl ; 
 int /*<<< orphan*/  intelfb_gpio_getsda ; 
 int /*<<< orphan*/  intelfb_gpio_setscl (struct intelfb_i2c_chan*,int) ; 
 int /*<<< orphan*/  intelfb_gpio_setsda (struct intelfb_i2c_chan*,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char const*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int intelfb_setup_i2c_bus(struct intelfb_info *dinfo,
				 struct intelfb_i2c_chan *chan,
				 const u32 reg, const char *name,
				 int class)
{
	int rc;

	chan->dinfo			= dinfo;
	chan->reg			= reg;
	snprintf(chan->adapter.name, sizeof(chan->adapter.name),
		 "intelfb %s", name);
	chan->adapter.class		= class;
	chan->adapter.owner		= THIS_MODULE;
	chan->adapter.algo_data		= &chan->algo;
	chan->adapter.dev.parent	= &chan->dinfo->pdev->dev;
	chan->algo.setsda		= intelfb_gpio_setsda;
	chan->algo.setscl		= intelfb_gpio_setscl;
	chan->algo.getsda		= intelfb_gpio_getsda;
	chan->algo.getscl		= intelfb_gpio_getscl;
	chan->algo.udelay		= 40;
	chan->algo.timeout		= 20;
	chan->algo.data			= chan;

	i2c_set_adapdata(&chan->adapter, chan);

	/* Raise SCL and SDA */
	intelfb_gpio_setsda(chan, 1);
	intelfb_gpio_setscl(chan, 1);
	udelay(20);

	rc = i2c_bit_add_bus(&chan->adapter);
	if (rc == 0)
		DBG_MSG("I2C bus %s registered.\n", name);
	else
		WRN_MSG("Failed to register I2C bus %s.\n", name);
	return rc;
}