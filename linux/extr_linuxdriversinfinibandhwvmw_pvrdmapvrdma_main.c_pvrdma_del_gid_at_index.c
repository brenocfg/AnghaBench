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
struct pvrdma_cmd_destroy_bind {int index; int /*<<< orphan*/  dest_gid; TYPE_1__ hdr; } ;
union pvrdma_cmd_req {struct pvrdma_cmd_destroy_bind destroy_bind; } ;
struct pvrdma_dev {struct pvrdma_cmd_destroy_bind* sgid_tbl; TYPE_2__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PVRDMA_CMD_DESTROY_BIND ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct pvrdma_cmd_destroy_bind*,int) ; 
 int /*<<< orphan*/  memset (struct pvrdma_cmd_destroy_bind*,int /*<<< orphan*/ ,int) ; 
 int pvrdma_cmd_post (struct pvrdma_dev*,union pvrdma_cmd_req*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pvrdma_del_gid_at_index(struct pvrdma_dev *dev, int index)
{
	int ret;
	union pvrdma_cmd_req req;
	struct pvrdma_cmd_destroy_bind *cmd_dest = &req.destroy_bind;

	/* Update sgid table. */
	if (!dev->sgid_tbl) {
		dev_warn(&dev->pdev->dev, "sgid table not initialized\n");
		return -EINVAL;
	}

	memset(cmd_dest, 0, sizeof(*cmd_dest));
	cmd_dest->hdr.cmd = PVRDMA_CMD_DESTROY_BIND;
	memcpy(cmd_dest->dest_gid, &dev->sgid_tbl[index], 16);
	cmd_dest->index = index;

	ret = pvrdma_cmd_post(dev, &req, NULL, 0);
	if (ret < 0) {
		dev_warn(&dev->pdev->dev,
			 "could not destroy binding, error: %d\n", ret);
		return ret;
	}
	memset(&dev->sgid_tbl[index], 0, 16);
	return 0;
}