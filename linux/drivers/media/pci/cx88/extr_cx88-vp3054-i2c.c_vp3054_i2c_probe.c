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
struct TYPE_9__ {TYPE_3__* algo_data; int /*<<< orphan*/  owner; int /*<<< orphan*/  name; TYPE_1__ dev; } ;
struct TYPE_8__ {struct cx8802_dev* data; } ;
struct vp3054_i2c_state {TYPE_4__ adap; TYPE_3__ algo; } ;
struct cx88_core {scalar_t__ boardnr; int /*<<< orphan*/  name; } ;
struct cx8802_dev {struct vp3054_i2c_state* vp3054; TYPE_2__* pci; struct cx88_core* core; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ CX88_BOARD_DNTV_LIVE_DVB_T_PRO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int i2c_bit_add_bus (TYPE_4__*) ; 
 int /*<<< orphan*/  i2c_set_adapdata (TYPE_4__*,struct cx8802_dev*) ; 
 int /*<<< orphan*/  kfree (struct vp3054_i2c_state*) ; 
 struct vp3054_i2c_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vp3054_bit_setscl (struct cx8802_dev*,int) ; 
 int /*<<< orphan*/  vp3054_bit_setsda (struct cx8802_dev*,int) ; 
 TYPE_3__ vp3054_i2c_algo_template ; 

int vp3054_i2c_probe(struct cx8802_dev *dev)
{
	struct cx88_core *core = dev->core;
	struct vp3054_i2c_state *vp3054_i2c;
	int rc;

	if (core->boardnr != CX88_BOARD_DNTV_LIVE_DVB_T_PRO)
		return 0;

	vp3054_i2c = kzalloc(sizeof(*vp3054_i2c), GFP_KERNEL);
	if (!vp3054_i2c)
		return -ENOMEM;
	dev->vp3054 = vp3054_i2c;

	vp3054_i2c->algo = vp3054_i2c_algo_template;

	vp3054_i2c->adap.dev.parent = &dev->pci->dev;
	strscpy(vp3054_i2c->adap.name, core->name,
		sizeof(vp3054_i2c->adap.name));
	vp3054_i2c->adap.owner = THIS_MODULE;
	vp3054_i2c->algo.data = dev;
	i2c_set_adapdata(&vp3054_i2c->adap, dev);
	vp3054_i2c->adap.algo_data = &vp3054_i2c->algo;

	vp3054_bit_setscl(dev, 1);
	vp3054_bit_setsda(dev, 1);

	rc = i2c_bit_add_bus(&vp3054_i2c->adap);
	if (rc != 0) {
		pr_err("vp3054_i2c register FAILED\n");

		kfree(dev->vp3054);
		dev->vp3054 = NULL;
	}

	return rc;
}