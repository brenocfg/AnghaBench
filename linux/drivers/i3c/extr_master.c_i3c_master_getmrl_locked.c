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
struct i3c_device_info {int bcr; int /*<<< orphan*/  max_ibi_len; int /*<<< orphan*/  max_read_len; int /*<<< orphan*/  dyn_addr; } ;
struct i3c_ccc_mrl {int /*<<< orphan*/  ibi_len; int /*<<< orphan*/  read_len; } ;
struct TYPE_2__ {int len; } ;
struct i3c_ccc_cmd_dest {TYPE_1__ payload; } ;
struct i3c_ccc_cmd {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int I3C_BCR_IBI_PAYLOAD ; 
 int /*<<< orphan*/  I3C_CCC_GETMRL ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i3c_ccc_cmd_dest_cleanup (struct i3c_ccc_cmd_dest*) ; 
 struct i3c_ccc_mrl* i3c_ccc_cmd_dest_init (struct i3c_ccc_cmd_dest*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i3c_ccc_cmd_init (struct i3c_ccc_cmd*,int,int /*<<< orphan*/ ,struct i3c_ccc_cmd_dest*,int) ; 
 int i3c_master_send_ccc_cmd_locked (struct i3c_master_controller*,struct i3c_ccc_cmd*) ; 

__attribute__((used)) static int i3c_master_getmrl_locked(struct i3c_master_controller *master,
				    struct i3c_device_info *info)
{
	struct i3c_ccc_cmd_dest dest;
	unsigned int expected_len;
	struct i3c_ccc_mrl *mrl;
	struct i3c_ccc_cmd cmd;
	int ret;

	mrl = i3c_ccc_cmd_dest_init(&dest, info->dyn_addr, sizeof(*mrl));
	if (!mrl)
		return -ENOMEM;

	/*
	 * When the device does not have IBI payload GETMRL only returns 2
	 * bytes of data.
	 */
	if (!(info->bcr & I3C_BCR_IBI_PAYLOAD))
		dest.payload.len -= 1;

	expected_len = dest.payload.len;
	i3c_ccc_cmd_init(&cmd, true, I3C_CCC_GETMRL, &dest, 1);
	ret = i3c_master_send_ccc_cmd_locked(master, &cmd);
	if (ret)
		goto out;

	if (dest.payload.len != expected_len) {
		ret = -EIO;
		goto out;
	}

	info->max_read_len = be16_to_cpu(mrl->read_len);

	if (info->bcr & I3C_BCR_IBI_PAYLOAD)
		info->max_ibi_len = mrl->ibi_len;

out:
	i3c_ccc_cmd_dest_cleanup(&dest);

	return ret;
}