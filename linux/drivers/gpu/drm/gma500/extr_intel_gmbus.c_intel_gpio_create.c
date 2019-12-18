#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct TYPE_5__ {int /*<<< orphan*/ * parent; } ;
struct i2c_adapter {TYPE_1__ dev; TYPE_4__* algo_data; int /*<<< orphan*/  owner; int /*<<< orphan*/  name; } ;
struct TYPE_8__ {struct intel_gpio* data; int /*<<< orphan*/  timeout; int /*<<< orphan*/  udelay; int /*<<< orphan*/  getscl; int /*<<< orphan*/  getsda; int /*<<< orphan*/  setscl; int /*<<< orphan*/  setsda; } ;
struct intel_gpio {int reg; struct i2c_adapter adapter; TYPE_4__ algo; struct drm_psb_private* dev_priv; } ;
struct drm_psb_private {TYPE_3__* dev; } ;
struct TYPE_7__ {TYPE_2__* pdev; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int const*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  GPIOA 133 
#define  GPIOB 132 
#define  GPIOC 131 
#define  GPIOD 130 
#define  GPIOE 129 
#define  GPIOF 128 
 int /*<<< orphan*/  I2C_RISEFALL_TIME ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  get_clock ; 
 int /*<<< orphan*/  get_data ; 
 scalar_t__ i2c_bit_add_bus (struct i2c_adapter*) ; 
 int /*<<< orphan*/  kfree (struct intel_gpio*) ; 
 struct intel_gpio* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_clock ; 
 int /*<<< orphan*/  set_data ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char) ; 
 int /*<<< orphan*/  usecs_to_jiffies (int) ; 

__attribute__((used)) static struct i2c_adapter *
intel_gpio_create(struct drm_psb_private *dev_priv, u32 pin)
{
	static const int map_pin_to_reg[] = {
		0,
		GPIOB,
		GPIOA,
		GPIOC,
		GPIOD,
		GPIOE,
		0,
		GPIOF,
	};
	struct intel_gpio *gpio;

	if (pin >= ARRAY_SIZE(map_pin_to_reg) || !map_pin_to_reg[pin])
		return NULL;

	gpio = kzalloc(sizeof(struct intel_gpio), GFP_KERNEL);
	if (gpio == NULL)
		return NULL;

	gpio->reg = map_pin_to_reg[pin];
	gpio->dev_priv = dev_priv;

	snprintf(gpio->adapter.name, sizeof(gpio->adapter.name),
		 "gma500 GPIO%c", "?BACDE?F"[pin]);
	gpio->adapter.owner = THIS_MODULE;
	gpio->adapter.algo_data	= &gpio->algo;
	gpio->adapter.dev.parent = &dev_priv->dev->pdev->dev;
	gpio->algo.setsda = set_data;
	gpio->algo.setscl = set_clock;
	gpio->algo.getsda = get_data;
	gpio->algo.getscl = get_clock;
	gpio->algo.udelay = I2C_RISEFALL_TIME;
	gpio->algo.timeout = usecs_to_jiffies(2200);
	gpio->algo.data = gpio;

	if (i2c_bit_add_bus(&gpio->adapter))
		goto out_free;

	return &gpio->adapter;

out_free:
	kfree(gpio);
	return NULL;
}