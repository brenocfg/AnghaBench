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
struct ssif_info {int ssif_debug; int /*<<< orphan*/  recv; scalar_t__ multi_pos; scalar_t__ rtc_us_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  I2C_SMBUS_BLOCK_DATA ; 
 int /*<<< orphan*/  I2C_SMBUS_READ ; 
 int SSIF_DEBUG_MSG ; 
 int /*<<< orphan*/  SSIF_IPMI_RESPONSE ; 
 int /*<<< orphan*/  msg_done_handler (struct ssif_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int ssif_i2c_send (struct ssif_info*,int /*<<< orphan*/  (*) (struct ssif_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ),int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void start_get(struct ssif_info *ssif_info)
{
	int rv;

	ssif_info->rtc_us_timer = 0;
	ssif_info->multi_pos = 0;

	rv = ssif_i2c_send(ssif_info, msg_done_handler, I2C_SMBUS_READ,
			  SSIF_IPMI_RESPONSE,
			  ssif_info->recv, I2C_SMBUS_BLOCK_DATA);
	if (rv < 0) {
		/* request failed, just return the error. */
		if (ssif_info->ssif_debug & SSIF_DEBUG_MSG)
			pr_info("Error from i2c_non_blocking_op(5)\n");

		msg_done_handler(ssif_info, -EIO, NULL, 0);
	}
}