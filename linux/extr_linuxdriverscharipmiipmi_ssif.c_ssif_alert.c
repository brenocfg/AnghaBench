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
struct ssif_info {int waiting_alert; int got_alert; scalar_t__ curr_msg; int /*<<< orphan*/  retry_timer; } ;
struct i2c_client {int dummy; } ;
typedef  enum i2c_alert_protocol { ____Placeholder_i2c_alert_protocol } i2c_alert_protocol ;

/* Variables and functions */
 int I2C_PROTOCOL_SMBUS_ALERT ; 
 int /*<<< orphan*/  alerts ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 struct ssif_info* i2c_get_clientdata (struct i2c_client*) ; 
 unsigned long* ipmi_ssif_lock_cond (struct ssif_info*,unsigned long*) ; 
 int /*<<< orphan*/  ipmi_ssif_unlock_cond (struct ssif_info*,unsigned long*) ; 
 int /*<<< orphan*/  ssif_inc_stat (struct ssif_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_get (struct ssif_info*) ; 

__attribute__((used)) static void ssif_alert(struct i2c_client *client, enum i2c_alert_protocol type,
		       unsigned int data)
{
	struct ssif_info *ssif_info = i2c_get_clientdata(client);
	unsigned long oflags, *flags;
	bool do_get = false;

	if (type != I2C_PROTOCOL_SMBUS_ALERT)
		return;

	ssif_inc_stat(ssif_info, alerts);

	flags = ipmi_ssif_lock_cond(ssif_info, &oflags);
	if (ssif_info->waiting_alert) {
		ssif_info->waiting_alert = false;
		del_timer(&ssif_info->retry_timer);
		do_get = true;
	} else if (ssif_info->curr_msg) {
		ssif_info->got_alert = true;
	}
	ipmi_ssif_unlock_cond(ssif_info, flags);
	if (do_get)
		start_get(ssif_info);
}