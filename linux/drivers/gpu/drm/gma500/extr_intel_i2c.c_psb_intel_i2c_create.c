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
struct TYPE_6__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_9__ {TYPE_1__ dev; TYPE_3__* algo_data; int /*<<< orphan*/  owner; int /*<<< orphan*/  name; } ;
struct TYPE_8__ {int udelay; struct psb_intel_i2c_chan* data; int /*<<< orphan*/  timeout; int /*<<< orphan*/  getscl; int /*<<< orphan*/  getsda; int /*<<< orphan*/  (* setscl ) (struct psb_intel_i2c_chan*,int) ;int /*<<< orphan*/  (* setsda ) (struct psb_intel_i2c_chan*,int) ;} ;
struct psb_intel_i2c_chan {TYPE_4__ adapter; TYPE_3__ algo; int /*<<< orphan*/  reg; struct drm_device* drm_dev; } ;
struct drm_device {TYPE_2__* pdev; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_NAME_SIZE ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  get_clock ; 
 int /*<<< orphan*/  get_data ; 
 scalar_t__ i2c_bit_add_bus (TYPE_4__*) ; 
 int /*<<< orphan*/  i2c_set_adapdata (TYPE_4__*,struct psb_intel_i2c_chan*) ; 
 int /*<<< orphan*/  kfree (struct psb_intel_i2c_chan*) ; 
 struct psb_intel_i2c_chan* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_clock (struct psb_intel_i2c_chan*,int) ; 
 int /*<<< orphan*/  set_data (struct psb_intel_i2c_chan*,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  usecs_to_jiffies (int) ; 

struct psb_intel_i2c_chan *psb_intel_i2c_create(struct drm_device *dev,
					const u32 reg, const char *name)
{
	struct psb_intel_i2c_chan *chan;

	chan = kzalloc(sizeof(struct psb_intel_i2c_chan), GFP_KERNEL);
	if (!chan)
		goto out_free;

	chan->drm_dev = dev;
	chan->reg = reg;
	snprintf(chan->adapter.name, I2C_NAME_SIZE, "intel drm %s", name);
	chan->adapter.owner = THIS_MODULE;
	chan->adapter.algo_data = &chan->algo;
	chan->adapter.dev.parent = &dev->pdev->dev;
	chan->algo.setsda = set_data;
	chan->algo.setscl = set_clock;
	chan->algo.getsda = get_data;
	chan->algo.getscl = get_clock;
	chan->algo.udelay = 20;
	chan->algo.timeout = usecs_to_jiffies(2200);
	chan->algo.data = chan;

	i2c_set_adapdata(&chan->adapter, chan);

	if (i2c_bit_add_bus(&chan->adapter))
		goto out_free;

	/* JJJ:  raise SCL and SDA? */
	set_data(chan, 1);
	set_clock(chan, 1);
	udelay(20);

	return chan;

out_free:
	kfree(chan);
	return NULL;
}