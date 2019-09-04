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
typedef  scalar_t__ u8 ;
struct wf_sensor {struct wf_ad7417_priv* priv; } ;
struct wf_ad7417_priv {int /*<<< orphan*/  lock; int /*<<< orphan*/  i2c; } ;
typedef  int s32 ;
typedef  scalar_t__ s16 ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 scalar_t__ be16_to_cpup (int /*<<< orphan*/ *) ; 
 int i2c_master_recv (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int i2c_master_send (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int wf_ad7417_temp_get(struct wf_sensor *sr, s32 *value)
{
	struct wf_ad7417_priv *pv = sr->priv;
	u8 buf[2];
	s16 raw;
	int rc;

	*value = 0;
	mutex_lock(&pv->lock);

	/* Read temp register */
	buf[0] = 0;
	rc = i2c_master_send(pv->i2c, buf, 1);
	if (rc < 0)
		goto error;
	rc = i2c_master_recv(pv->i2c, buf, 2);
	if (rc < 0)
		goto error;

	/* Read a a 16-bit signed value */
	raw = be16_to_cpup((__le16 *)buf);

	/* Convert 8.8-bit to 16.16 fixed point */
	*value = ((s32)raw) << 8;

	mutex_unlock(&pv->lock);
	return 0;

error:
	mutex_unlock(&pv->lock);
	return -1;
}