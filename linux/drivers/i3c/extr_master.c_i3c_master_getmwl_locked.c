#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct i3c_master_controller {int dummy; } ;
struct i3c_device_info {int /*<<< orphan*/  max_write_len; int /*<<< orphan*/  dyn_addr; } ;
struct i3c_ccc_mwl {int /*<<< orphan*/  len; } ;
struct TYPE_2__ {int len; } ;
struct i3c_ccc_cmd_dest {TYPE_1__ payload; } ;
struct i3c_ccc_cmd {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  I3C_CCC_GETMWL ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i3c_ccc_cmd_dest_cleanup (struct i3c_ccc_cmd_dest*) ; 
 struct i3c_ccc_mwl* i3c_ccc_cmd_dest_init (struct i3c_ccc_cmd_dest*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i3c_ccc_cmd_init (struct i3c_ccc_cmd*,int,int /*<<< orphan*/ ,struct i3c_ccc_cmd_dest*,int) ; 
 int i3c_master_send_ccc_cmd_locked (struct i3c_master_controller*,struct i3c_ccc_cmd*) ; 

__attribute__((used)) static int i3c_master_getmwl_locked(struct i3c_master_controller *master,
				    struct i3c_device_info *info)
{
	struct i3c_ccc_cmd_dest dest;
	struct i3c_ccc_mwl *mwl;
	struct i3c_ccc_cmd cmd;
	int ret;

	mwl = i3c_ccc_cmd_dest_init(&dest, info->dyn_addr, sizeof(*mwl));
	if (!mwl)
		return -ENOMEM;

	i3c_ccc_cmd_init(&cmd, true, I3C_CCC_GETMWL, &dest, 1);
	ret = i3c_master_send_ccc_cmd_locked(master, &cmd);
	if (ret)
		goto out;

	if (dest.payload.len != sizeof(*mwl)) {
		ret = -EIO;
		goto out;
	}

	info->max_write_len = be16_to_cpu(mwl->len);

out:
	i3c_ccc_cmd_dest_cleanup(&dest);

	return ret;
}