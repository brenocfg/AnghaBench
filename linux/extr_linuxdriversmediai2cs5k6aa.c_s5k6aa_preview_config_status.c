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
typedef  scalar_t__ u16 ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  REG_G_PREV_CFG_ERROR ; 
 int /*<<< orphan*/  debug ; 
 int s5k6aa_read (struct i2c_client*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct i2c_client*,char*,scalar_t__,int) ; 

__attribute__((used)) static int s5k6aa_preview_config_status(struct i2c_client *client)
{
	u16 error = 0;
	int ret = s5k6aa_read(client, REG_G_PREV_CFG_ERROR, &error);

	v4l2_dbg(1, debug, client, "error: 0x%x (%d)\n", error, ret);
	return ret ? ret : (error ? -EINVAL : 0);
}