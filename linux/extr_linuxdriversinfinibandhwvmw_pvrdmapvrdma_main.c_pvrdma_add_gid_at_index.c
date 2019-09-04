#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  cmd; } ;
struct pvrdma_cmd_create_bind {int vlan; int index; int /*<<< orphan*/  gid_type; int /*<<< orphan*/  mtu; int /*<<< orphan*/ * new_gid; TYPE_1__ hdr; } ;
union pvrdma_cmd_req {struct pvrdma_cmd_create_bind create_bind; } ;
union ib_gid {union ib_gid const* raw; } ;
typedef  int /*<<< orphan*/  u8 ;
struct pvrdma_dev {int /*<<< orphan*/ * sgid_tbl; TYPE_2__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int /*<<< orphan*/  IB_MTU_1024 ; 
 int /*<<< orphan*/  PVRDMA_CMD_CREATE_BIND ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  ib_mtu_enum_to_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,union ib_gid const*,int) ; 
 int /*<<< orphan*/  memset (struct pvrdma_cmd_create_bind*,int /*<<< orphan*/ ,int) ; 
 int pvrdma_cmd_post (struct pvrdma_dev*,union pvrdma_cmd_req*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pvrdma_add_gid_at_index(struct pvrdma_dev *dev,
				   const union ib_gid *gid,
				   u8 gid_type,
				   int index)
{
	int ret;
	union pvrdma_cmd_req req;
	struct pvrdma_cmd_create_bind *cmd_bind = &req.create_bind;

	if (!dev->sgid_tbl) {
		dev_warn(&dev->pdev->dev, "sgid table not initialized\n");
		return -EINVAL;
	}

	memset(cmd_bind, 0, sizeof(*cmd_bind));
	cmd_bind->hdr.cmd = PVRDMA_CMD_CREATE_BIND;
	memcpy(cmd_bind->new_gid, gid->raw, 16);
	cmd_bind->mtu = ib_mtu_enum_to_int(IB_MTU_1024);
	cmd_bind->vlan = 0xfff;
	cmd_bind->index = index;
	cmd_bind->gid_type = gid_type;

	ret = pvrdma_cmd_post(dev, &req, NULL, 0);
	if (ret < 0) {
		dev_warn(&dev->pdev->dev,
			 "could not create binding, error: %d\n", ret);
		return -EFAULT;
	}
	memcpy(&dev->sgid_tbl[index], gid, sizeof(*gid));
	return 0;
}