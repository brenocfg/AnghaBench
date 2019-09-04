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
typedef  int u16 ;
struct wf_sensor {int /*<<< orphan*/  name; struct wf_ad7417_priv* priv; } ;
struct wf_ad7417_priv {int config; int /*<<< orphan*/  lock; TYPE_1__* i2c; struct wf_sensor* sensors; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int be16_to_cpup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int i2c_master_recv (TYPE_1__*,int*,int) ; 
 int i2c_master_send (TYPE_1__*,int*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wf_ad7417_adc_convert (struct wf_ad7417_priv*,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int wf_ad7417_adc_get(struct wf_sensor *sr, s32 *value)
{
	struct wf_ad7417_priv *pv = sr->priv;
	int chan = sr - pv->sensors;
	int i, rc;
	u8 buf[2];
	u16 raw;

	*value = 0;
	mutex_lock(&pv->lock);
	for (i = 0; i < 10; i++) {
		/* Set channel */
		buf[0] = 1;
		buf[1] = (pv->config & 0x1f) | (chan << 5);
		rc = i2c_master_send(pv->i2c, buf, 2);
		if (rc < 0)
			goto error;

		/* Wait for conversion */
		msleep(1);

		/* Switch to data register */
		buf[0] = 4;
		rc = i2c_master_send(pv->i2c, buf, 1);
		if (rc < 0)
			goto error;

		/* Read result */
		rc = i2c_master_recv(pv->i2c, buf, 2);
		if (rc < 0)
			goto error;

		/* Read a a 16-bit signed value */
		raw = be16_to_cpup((__le16 *)buf) >> 6;
		wf_ad7417_adc_convert(pv, chan, raw, value);

		dev_vdbg(&pv->i2c->dev, "ADC chan %d [%s]"
			 " raw value: 0x%x, conv to: 0x%08x\n",
			 chan, sr->name, raw, *value);

		mutex_unlock(&pv->lock);
		return 0;

	error:
		dev_dbg(&pv->i2c->dev,
			  "Error reading ADC, try %d...\n", i);
		if (i < 9)
			msleep(10);
	}
	mutex_unlock(&pv->lock);
	return -1;
}