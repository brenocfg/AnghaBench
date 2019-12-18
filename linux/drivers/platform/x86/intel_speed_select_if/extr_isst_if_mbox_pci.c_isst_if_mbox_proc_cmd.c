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
typedef  int /*<<< orphan*/  u8 ;
struct pci_dev {int dummy; } ;
struct isst_if_mbox_cmd {int /*<<< orphan*/  req_data; int /*<<< orphan*/  parameter; int /*<<< orphan*/  logical_cpu; int /*<<< orphan*/  sub_command; int /*<<< orphan*/  command; } ;
struct isst_if_device {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 long EINVAL ; 
 long EPERM ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 struct pci_dev* isst_if_get_pci_dev (int /*<<< orphan*/ ,int,int,int) ; 
 int isst_if_mbox_cmd (struct pci_dev*,struct isst_if_mbox_cmd*) ; 
 scalar_t__ isst_if_mbox_cmd_invalid (struct isst_if_mbox_cmd*) ; 
 scalar_t__ isst_if_mbox_cmd_set_req (struct isst_if_mbox_cmd*) ; 
 int isst_store_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct isst_if_device* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static long isst_if_mbox_proc_cmd(u8 *cmd_ptr, int *write_only, int resume)
{
	struct isst_if_mbox_cmd *mbox_cmd;
	struct isst_if_device *punit_dev;
	struct pci_dev *pdev;
	int ret;

	mbox_cmd = (struct isst_if_mbox_cmd *)cmd_ptr;

	if (isst_if_mbox_cmd_invalid(mbox_cmd))
		return -EINVAL;

	if (isst_if_mbox_cmd_set_req(mbox_cmd) && !capable(CAP_SYS_ADMIN))
		return -EPERM;

	pdev = isst_if_get_pci_dev(mbox_cmd->logical_cpu, 1, 30, 1);
	if (!pdev)
		return -EINVAL;

	punit_dev = pci_get_drvdata(pdev);
	if (!punit_dev)
		return -EINVAL;

	/*
	 * Basically we are allowing one complete mailbox transaction on
	 * a mapped PCI device at a time.
	 */
	mutex_lock(&punit_dev->mutex);
	ret = isst_if_mbox_cmd(pdev, mbox_cmd);
	if (!ret && !resume && isst_if_mbox_cmd_set_req(mbox_cmd))
		ret = isst_store_cmd(mbox_cmd->command,
				     mbox_cmd->sub_command,
				     mbox_cmd->logical_cpu, 1,
				     mbox_cmd->parameter,
				     mbox_cmd->req_data);
	mutex_unlock(&punit_dev->mutex);
	if (ret)
		return ret;

	*write_only = 0;

	return 0;
}