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
typedef  int /*<<< orphan*/  u16 ;
struct vadc_priv {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; int /*<<< orphan*/  complete; scalar_t__ poll_eoc; } ;
struct vadc_channel_prop {int /*<<< orphan*/  avg_samples; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  VADC_CONV_REQ ; 
 int /*<<< orphan*/  VADC_CONV_REQ_SET ; 
 int VADC_CONV_TIME_MIN_US ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int vadc_configure (struct vadc_priv*,struct vadc_channel_prop*) ; 
 int vadc_poll_wait_eoc (struct vadc_priv*,int) ; 
 int vadc_read_result (struct vadc_priv*,int /*<<< orphan*/ *) ; 
 int vadc_set_state (struct vadc_priv*,int) ; 
 int vadc_write (struct vadc_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static int vadc_do_conversion(struct vadc_priv *vadc,
			      struct vadc_channel_prop *prop, u16 *data)
{
	unsigned int timeout;
	int ret;

	mutex_lock(&vadc->lock);

	ret = vadc_configure(vadc, prop);
	if (ret)
		goto unlock;

	if (!vadc->poll_eoc)
		reinit_completion(&vadc->complete);

	ret = vadc_set_state(vadc, true);
	if (ret)
		goto unlock;

	ret = vadc_write(vadc, VADC_CONV_REQ, VADC_CONV_REQ_SET);
	if (ret)
		goto err_disable;

	timeout = BIT(prop->avg_samples) * VADC_CONV_TIME_MIN_US * 2;

	if (vadc->poll_eoc) {
		ret = vadc_poll_wait_eoc(vadc, timeout);
	} else {
		ret = wait_for_completion_timeout(&vadc->complete, timeout);
		if (!ret) {
			ret = -ETIMEDOUT;
			goto err_disable;
		}

		/* Double check conversion status */
		ret = vadc_poll_wait_eoc(vadc, VADC_CONV_TIME_MIN_US);
		if (ret)
			goto err_disable;
	}

	ret = vadc_read_result(vadc, data);

err_disable:
	vadc_set_state(vadc, false);
	if (ret)
		dev_err(vadc->dev, "conversion failed\n");
unlock:
	mutex_unlock(&vadc->lock);
	return ret;
}