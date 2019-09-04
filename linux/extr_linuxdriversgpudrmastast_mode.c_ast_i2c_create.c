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
struct drm_device {TYPE_2__* pdev; } ;
struct TYPE_6__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_9__ {TYPE_3__* algo_data; int /*<<< orphan*/  name; TYPE_1__ dev; int /*<<< orphan*/  class; int /*<<< orphan*/  owner; } ;
struct TYPE_8__ {int udelay; int timeout; int /*<<< orphan*/  getscl; int /*<<< orphan*/  getsda; int /*<<< orphan*/  setscl; int /*<<< orphan*/  setsda; struct ast_i2c_chan* data; } ;
struct ast_i2c_chan {TYPE_4__ adapter; TYPE_3__ bit; struct drm_device* dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_CLASS_DDC ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  get_clock ; 
 int /*<<< orphan*/  get_data ; 
 int i2c_bit_add_bus (TYPE_4__*) ; 
 int /*<<< orphan*/  i2c_set_adapdata (TYPE_4__*,struct ast_i2c_chan*) ; 
 int /*<<< orphan*/  kfree (struct ast_i2c_chan*) ; 
 struct ast_i2c_chan* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_clock ; 
 int /*<<< orphan*/  set_data ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static struct ast_i2c_chan *ast_i2c_create(struct drm_device *dev)
{
	struct ast_i2c_chan *i2c;
	int ret;

	i2c = kzalloc(sizeof(struct ast_i2c_chan), GFP_KERNEL);
	if (!i2c)
		return NULL;

	i2c->adapter.owner = THIS_MODULE;
	i2c->adapter.class = I2C_CLASS_DDC;
	i2c->adapter.dev.parent = &dev->pdev->dev;
	i2c->dev = dev;
	i2c_set_adapdata(&i2c->adapter, i2c);
	snprintf(i2c->adapter.name, sizeof(i2c->adapter.name),
		 "AST i2c bit bus");
	i2c->adapter.algo_data = &i2c->bit;

	i2c->bit.udelay = 20;
	i2c->bit.timeout = 2;
	i2c->bit.data = i2c;
	i2c->bit.setsda = set_data;
	i2c->bit.setscl = set_clock;
	i2c->bit.getsda = get_data;
	i2c->bit.getscl = get_clock;
	ret = i2c_bit_add_bus(&i2c->adapter);
	if (ret) {
		DRM_ERROR("Failed to register bit i2c\n");
		goto out_free;
	}

	return i2c;
out_free:
	kfree(i2c);
	return NULL;
}