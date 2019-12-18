#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct drm_device {TYPE_2__* pdev; } ;
struct TYPE_7__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_10__ {TYPE_3__* algo_data; int /*<<< orphan*/  name; int /*<<< orphan*/ * algo; TYPE_1__ dev; int /*<<< orphan*/  class; int /*<<< orphan*/  owner; } ;
struct TYPE_9__ {int udelay; struct amdgpu_i2c_chan* data; int /*<<< orphan*/  timeout; int /*<<< orphan*/  getscl; int /*<<< orphan*/  getsda; int /*<<< orphan*/  setscl; int /*<<< orphan*/  setsda; int /*<<< orphan*/  post_xfer; int /*<<< orphan*/  pre_xfer; } ;
struct amdgpu_i2c_bus_rec {scalar_t__ hw_capable; scalar_t__ mm_i2c; } ;
struct amdgpu_i2c_chan {TYPE_4__ adapter; TYPE_3__ bit; int /*<<< orphan*/  mutex; struct drm_device* dev; struct amdgpu_i2c_bus_rec rec; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,char const*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_CLASS_DDC ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  amdgpu_atombios_i2c_algo ; 
 scalar_t__ amdgpu_hw_i2c ; 
 int /*<<< orphan*/  amdgpu_i2c_get_clock ; 
 int /*<<< orphan*/  amdgpu_i2c_get_data ; 
 int /*<<< orphan*/  amdgpu_i2c_post_xfer ; 
 int /*<<< orphan*/  amdgpu_i2c_pre_xfer ; 
 int /*<<< orphan*/  amdgpu_i2c_set_clock ; 
 int /*<<< orphan*/  amdgpu_i2c_set_data ; 
 int i2c_add_adapter (TYPE_4__*) ; 
 int i2c_bit_add_bus (TYPE_4__*) ; 
 int /*<<< orphan*/  i2c_set_adapdata (TYPE_4__*,struct amdgpu_i2c_chan*) ; 
 int /*<<< orphan*/  kfree (struct amdgpu_i2c_chan*) ; 
 struct amdgpu_i2c_chan* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char const*) ; 
 int /*<<< orphan*/  usecs_to_jiffies (int) ; 

struct amdgpu_i2c_chan *amdgpu_i2c_create(struct drm_device *dev,
					  const struct amdgpu_i2c_bus_rec *rec,
					  const char *name)
{
	struct amdgpu_i2c_chan *i2c;
	int ret;

	/* don't add the mm_i2c bus unless hw_i2c is enabled */
	if (rec->mm_i2c && (amdgpu_hw_i2c == 0))
		return NULL;

	i2c = kzalloc(sizeof(struct amdgpu_i2c_chan), GFP_KERNEL);
	if (i2c == NULL)
		return NULL;

	i2c->rec = *rec;
	i2c->adapter.owner = THIS_MODULE;
	i2c->adapter.class = I2C_CLASS_DDC;
	i2c->adapter.dev.parent = &dev->pdev->dev;
	i2c->dev = dev;
	i2c_set_adapdata(&i2c->adapter, i2c);
	mutex_init(&i2c->mutex);
	if (rec->hw_capable &&
	    amdgpu_hw_i2c) {
		/* hw i2c using atom */
		snprintf(i2c->adapter.name, sizeof(i2c->adapter.name),
			 "AMDGPU i2c hw bus %s", name);
		i2c->adapter.algo = &amdgpu_atombios_i2c_algo;
		ret = i2c_add_adapter(&i2c->adapter);
		if (ret)
			goto out_free;
	} else {
		/* set the amdgpu bit adapter */
		snprintf(i2c->adapter.name, sizeof(i2c->adapter.name),
			 "AMDGPU i2c bit bus %s", name);
		i2c->adapter.algo_data = &i2c->bit;
		i2c->bit.pre_xfer = amdgpu_i2c_pre_xfer;
		i2c->bit.post_xfer = amdgpu_i2c_post_xfer;
		i2c->bit.setsda = amdgpu_i2c_set_data;
		i2c->bit.setscl = amdgpu_i2c_set_clock;
		i2c->bit.getsda = amdgpu_i2c_get_data;
		i2c->bit.getscl = amdgpu_i2c_get_clock;
		i2c->bit.udelay = 10;
		i2c->bit.timeout = usecs_to_jiffies(2200);	/* from VESA */
		i2c->bit.data = i2c;
		ret = i2c_bit_add_bus(&i2c->adapter);
		if (ret) {
			DRM_ERROR("Failed to register bit i2c %s\n", name);
			goto out_free;
		}
	}

	return i2c;
out_free:
	kfree(i2c);
	return NULL;

}