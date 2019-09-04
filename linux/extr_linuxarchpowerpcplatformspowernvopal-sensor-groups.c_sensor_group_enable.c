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
typedef  int /*<<< orphan*/  u32 ;
struct opal_msg {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int OPAL_ASYNC_COMPLETION ; 
 int opal_async_get_token_interruptible () ; 
 int /*<<< orphan*/  opal_async_release_token (int) ; 
 int opal_async_wait_response (int,struct opal_msg*) ; 
 int opal_error_code (int) ; 
 int opal_get_async_rc (struct opal_msg) ; 
 int opal_sensor_group_enable (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pr_devel (char*) ; 

int sensor_group_enable(u32 handle, bool enable)
{
	struct opal_msg msg;
	int token, ret;

	token = opal_async_get_token_interruptible();
	if (token < 0)
		return token;

	ret = opal_sensor_group_enable(handle, token, enable);
	if (ret == OPAL_ASYNC_COMPLETION) {
		ret = opal_async_wait_response(token, &msg);
		if (ret) {
			pr_devel("Failed to wait for the async response\n");
			ret = -EIO;
			goto out;
		}
		ret = opal_error_code(opal_get_async_rc(msg));
	} else {
		ret = opal_error_code(ret);
	}

out:
	opal_async_release_token(token);
	return ret;
}