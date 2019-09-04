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
struct TYPE_6__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_9__ {TYPE_3__* algo_data; int /*<<< orphan*/  name; TYPE_1__ dev; int /*<<< orphan*/  class; int /*<<< orphan*/  owner; } ;
struct TYPE_8__ {int udelay; int timeout; int /*<<< orphan*/  getscl; int /*<<< orphan*/  getsda; int /*<<< orphan*/  setscl; int /*<<< orphan*/  setsda; struct mga_i2c_chan* data; } ;
struct mga_i2c_chan {int data; int clock; TYPE_4__ adapter; TYPE_3__ bit; struct drm_device* dev; } ;
struct mga_device {int type; } ;
struct drm_device {TYPE_2__* pdev; struct mga_device* dev_private; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  G200_EH 135 
#define  G200_EH3 134 
#define  G200_ER 133 
#define  G200_EV 132 
#define  G200_EW3 131 
#define  G200_SE_A 130 
#define  G200_SE_B 129 
#define  G200_WB 128 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_CLASS_DDC ; 
 int /*<<< orphan*/  MGA1064_GEN_IO_CTL ; 
 int /*<<< orphan*/  MGA1064_GEN_IO_CTL2 ; 
 int /*<<< orphan*/  MGA1064_GEN_IO_DATA ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  WREG_DAC (int /*<<< orphan*/ ,int) ; 
 int i2c_bit_add_bus (TYPE_4__*) ; 
 int /*<<< orphan*/  i2c_set_adapdata (TYPE_4__*,struct mga_i2c_chan*) ; 
 int /*<<< orphan*/  kfree (struct mga_i2c_chan*) ; 
 struct mga_i2c_chan* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mga_gpio_getscl ; 
 int /*<<< orphan*/  mga_gpio_getsda ; 
 int /*<<< orphan*/  mga_gpio_setscl ; 
 int /*<<< orphan*/  mga_gpio_setsda ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*) ; 

struct mga_i2c_chan *mgag200_i2c_create(struct drm_device *dev)
{
	struct mga_device *mdev = dev->dev_private;
	struct mga_i2c_chan *i2c;
	int ret;
	int data, clock;

	WREG_DAC(MGA1064_GEN_IO_CTL2, 1);
	WREG_DAC(MGA1064_GEN_IO_DATA, 0xff);
	WREG_DAC(MGA1064_GEN_IO_CTL, 0);

	switch (mdev->type) {
	case G200_SE_A:
	case G200_SE_B:
	case G200_EV:
	case G200_WB:
	case G200_EW3:
		data = 1;
		clock = 2;
		break;
	case G200_EH:
	case G200_EH3:
	case G200_ER:
		data = 2;
		clock = 1;
		break;
	default:
		data = 2;
		clock = 8;
		break;
	}

	i2c = kzalloc(sizeof(struct mga_i2c_chan), GFP_KERNEL);
	if (!i2c)
		return NULL;

	i2c->data = data;
	i2c->clock = clock;
	i2c->adapter.owner = THIS_MODULE;
	i2c->adapter.class = I2C_CLASS_DDC;
	i2c->adapter.dev.parent = &dev->pdev->dev;
	i2c->dev = dev;
	i2c_set_adapdata(&i2c->adapter, i2c);
	snprintf(i2c->adapter.name, sizeof(i2c->adapter.name), "mga i2c");

	i2c->adapter.algo_data = &i2c->bit;

	i2c->bit.udelay = 10;
	i2c->bit.timeout = 2;
	i2c->bit.data = i2c;
	i2c->bit.setsda		= mga_gpio_setsda;
	i2c->bit.setscl		= mga_gpio_setscl;
	i2c->bit.getsda		= mga_gpio_getsda;
	i2c->bit.getscl		= mga_gpio_getscl;

	ret = i2c_bit_add_bus(&i2c->adapter);
	if (ret) {
		kfree(i2c);
		i2c = NULL;
	}
	return i2c;
}