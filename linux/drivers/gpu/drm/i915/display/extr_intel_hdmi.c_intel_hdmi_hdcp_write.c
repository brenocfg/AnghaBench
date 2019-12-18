#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u8 ;
struct intel_hdmi {int /*<<< orphan*/  ddc_bus; } ;
struct TYPE_5__ {TYPE_1__* dev; } ;
struct TYPE_6__ {TYPE_2__ base; } ;
struct intel_digital_port {TYPE_3__ base; struct intel_hdmi hdmi; } ;
struct i2c_msg {size_t len; unsigned int* buf; scalar_t__ flags; int /*<<< orphan*/  addr; } ;
struct i2c_adapter {int dummy; } ;
struct drm_i915_private {int dummy; } ;
struct TYPE_4__ {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_HDCP_DDC_ADDR ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int i2c_transfer (struct i2c_adapter*,struct i2c_msg*,int) ; 
 struct i2c_adapter* intel_gmbus_get_adapter (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (unsigned int*) ; 
 unsigned int* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned int*,void*,size_t) ; 

__attribute__((used)) static int intel_hdmi_hdcp_write(struct intel_digital_port *intel_dig_port,
				 unsigned int offset, void *buffer, size_t size)
{
	struct intel_hdmi *hdmi = &intel_dig_port->hdmi;
	struct drm_i915_private *dev_priv =
		intel_dig_port->base.base.dev->dev_private;
	struct i2c_adapter *adapter = intel_gmbus_get_adapter(dev_priv,
							      hdmi->ddc_bus);
	int ret;
	u8 *write_buf;
	struct i2c_msg msg;

	write_buf = kzalloc(size + 1, GFP_KERNEL);
	if (!write_buf)
		return -ENOMEM;

	write_buf[0] = offset & 0xff;
	memcpy(&write_buf[1], buffer, size);

	msg.addr = DRM_HDCP_DDC_ADDR;
	msg.flags = 0,
	msg.len = size + 1,
	msg.buf = write_buf;

	ret = i2c_transfer(adapter, &msg, 1);
	if (ret == 1)
		ret = 0;
	else if (ret >= 0)
		ret = -EIO;

	kfree(write_buf);
	return ret;
}