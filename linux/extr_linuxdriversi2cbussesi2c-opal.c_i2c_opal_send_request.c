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
struct opal_i2c_request {int dummy; } ;

/* Variables and functions */
 int ERESTARTSYS ; 
 int OPAL_ASYNC_COMPLETION ; 
 int OPAL_SUCCESS ; 
 int i2c_opal_translate_error (int) ; 
 int opal_async_get_token_interruptible () ; 
 int /*<<< orphan*/  opal_async_release_token (int) ; 
 int opal_async_wait_response (int,struct opal_msg*) ; 
 int opal_get_async_rc (struct opal_msg) ; 
 int opal_i2c_request (int,int /*<<< orphan*/ ,struct opal_i2c_request*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int i2c_opal_send_request(u32 bus_id, struct opal_i2c_request *req)
{
	struct opal_msg msg;
	int token, rc;

	token = opal_async_get_token_interruptible();
	if (token < 0) {
		if (token != -ERESTARTSYS)
			pr_err("Failed to get the async token\n");

		return token;
	}

	rc = opal_i2c_request(token, bus_id, req);
	if (rc != OPAL_ASYNC_COMPLETION) {
		rc = i2c_opal_translate_error(rc);
		goto exit;
	}

	rc = opal_async_wait_response(token, &msg);
	if (rc)
		goto exit;

	rc = opal_get_async_rc(msg);
	if (rc != OPAL_SUCCESS) {
		rc = i2c_opal_translate_error(rc);
		goto exit;
	}

exit:
	opal_async_release_token(token);
	return rc;
}