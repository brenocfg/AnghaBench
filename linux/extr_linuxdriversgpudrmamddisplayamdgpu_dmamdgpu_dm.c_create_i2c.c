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
struct ddc_service {TYPE_1__* ctx; } ;
struct TYPE_6__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_8__ {int /*<<< orphan*/  name; int /*<<< orphan*/ * algo; TYPE_2__ dev; int /*<<< orphan*/  class; int /*<<< orphan*/  owner; } ;
struct amdgpu_i2c_adapter {struct ddc_service* ddc_service; TYPE_4__ base; } ;
struct amdgpu_device {TYPE_3__* pdev; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {struct amdgpu_device* driver_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_CLASS_DDC ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  amdgpu_dm_i2c_algo ; 
 int /*<<< orphan*/  i2c_set_adapdata (TYPE_4__*,struct amdgpu_i2c_adapter*) ; 
 struct amdgpu_i2c_adapter* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 

__attribute__((used)) static struct amdgpu_i2c_adapter *
create_i2c(struct ddc_service *ddc_service,
	   int link_index,
	   int *res)
{
	struct amdgpu_device *adev = ddc_service->ctx->driver_context;
	struct amdgpu_i2c_adapter *i2c;

	i2c = kzalloc(sizeof(struct amdgpu_i2c_adapter), GFP_KERNEL);
	if (!i2c)
		return NULL;
	i2c->base.owner = THIS_MODULE;
	i2c->base.class = I2C_CLASS_DDC;
	i2c->base.dev.parent = &adev->pdev->dev;
	i2c->base.algo = &amdgpu_dm_i2c_algo;
	snprintf(i2c->base.name, sizeof(i2c->base.name), "AMDGPU DM i2c hw bus %d", link_index);
	i2c_set_adapdata(&i2c->base, i2c);
	i2c->ddc_service = ddc_service;

	return i2c;
}