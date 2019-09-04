#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct wf_ad7417_priv {int config; TYPE_1__* i2c; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_master_recv (TYPE_1__*,int*,int) ; 
 int i2c_master_send (TYPE_1__*,int*,int) ; 

__attribute__((used)) static void wf_ad7417_init_chip(struct wf_ad7417_priv *pv)
{
	int rc;
	u8 buf[2];
	u8 config = 0;

	/*
	 * Read ADC the configuration register and cache it. We
	 * also make sure Config2 contains proper values, I've seen
	 * cases where we got stale grabage in there, thus preventing
	 * proper reading of conv. values
	 */

	/* Clear Config2 */
	buf[0] = 5;
	buf[1] = 0;
	i2c_master_send(pv->i2c, buf, 2);

	/* Read & cache Config1 */
	buf[0] = 1;
	rc = i2c_master_send(pv->i2c, buf, 1);
	if (rc > 0) {
		rc = i2c_master_recv(pv->i2c, buf, 1);
		if (rc > 0) {
			config = buf[0];

			dev_dbg(&pv->i2c->dev, "ADC config reg: %02x\n",
				config);

			/* Disable shutdown mode */
			config &= 0xfe;
			buf[0] = 1;
			buf[1] = config;
			rc = i2c_master_send(pv->i2c, buf, 2);
		}
	}
	if (rc <= 0)
		dev_err(&pv->i2c->dev, "Error reading ADC config\n");

	pv->config = config;
}