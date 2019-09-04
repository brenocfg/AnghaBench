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
struct s5k6aa {int /*<<< orphan*/  sd; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  REG_FW_APIVER ; 
 int /*<<< orphan*/  REG_FW_REVISION ; 
 scalar_t__ S5K6AAFX_FW_APIVER ; 
 int s5k6aa_read (struct i2c_client*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int s5k6aa_set_ahb_address (struct i2c_client*) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_info (int /*<<< orphan*/ *,char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int s5k6aa_check_fw_revision(struct s5k6aa *s5k6aa)
{
	struct i2c_client *client = v4l2_get_subdevdata(&s5k6aa->sd);
	u16 api_ver = 0, fw_rev = 0;

	int ret = s5k6aa_set_ahb_address(client);

	if (!ret)
		ret = s5k6aa_read(client, REG_FW_APIVER, &api_ver);
	if (!ret)
		ret = s5k6aa_read(client, REG_FW_REVISION, &fw_rev);
	if (ret) {
		v4l2_err(&s5k6aa->sd, "FW revision check failed!\n");
		return ret;
	}

	v4l2_info(&s5k6aa->sd, "FW API ver.: 0x%X, FW rev.: 0x%X\n",
		  api_ver, fw_rev);

	return api_ver == S5K6AAFX_FW_APIVER ? 0 : -ENODEV;
}