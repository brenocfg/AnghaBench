#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct dw_hdmi_i2c {int is_regaddr; unsigned char slave_reg; int /*<<< orphan*/  cmp; } ;
struct dw_hdmi {struct dw_hdmi_i2c* i2c; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_I2CM_ADDRESS ; 
 int /*<<< orphan*/  HDMI_I2CM_DATAO ; 
 int /*<<< orphan*/  HDMI_I2CM_OPERATION ; 
 int /*<<< orphan*/  HDMI_I2CM_OPERATION_WRITE ; 
 int dw_hdmi_i2c_wait (struct dw_hdmi*) ; 
 int /*<<< orphan*/  hdmi_writeb (struct dw_hdmi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dw_hdmi_i2c_write(struct dw_hdmi *hdmi,
			     unsigned char *buf, unsigned int length)
{
	struct dw_hdmi_i2c *i2c = hdmi->i2c;
	int ret;

	if (!i2c->is_regaddr) {
		/* Use the first write byte as register address */
		i2c->slave_reg = buf[0];
		length--;
		buf++;
		i2c->is_regaddr = true;
	}

	while (length--) {
		reinit_completion(&i2c->cmp);

		hdmi_writeb(hdmi, *buf++, HDMI_I2CM_DATAO);
		hdmi_writeb(hdmi, i2c->slave_reg++, HDMI_I2CM_ADDRESS);
		hdmi_writeb(hdmi, HDMI_I2CM_OPERATION_WRITE,
			    HDMI_I2CM_OPERATION);

		ret = dw_hdmi_i2c_wait(hdmi);
		if (ret)
			return ret;
	}

	return 0;
}