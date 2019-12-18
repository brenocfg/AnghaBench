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
typedef  int u32 ;
struct pci_dev {int dummy; } ;
struct isst_if_mbox_cmd {int req_data; int parameter; int sub_command; int command; int resp_data; } ;

/* Variables and functions */
 int BIT_ULL (int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 int ENXIO ; 
 int GENMASK_ULL (int,int /*<<< orphan*/ ) ; 
 int OS_MAILBOX_RETRY_COUNT ; 
 int /*<<< orphan*/  PUNIT_MAILBOX_BUSY_BIT ; 
 int /*<<< orphan*/  PUNIT_MAILBOX_DATA ; 
 int /*<<< orphan*/  PUNIT_MAILBOX_INTERFACE ; 
 int pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int pci_write_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int isst_if_mbox_cmd(struct pci_dev *pdev,
			    struct isst_if_mbox_cmd *mbox_cmd)
{
	u32 retries, data;
	int ret;

	/* Poll for rb bit == 0 */
	retries = OS_MAILBOX_RETRY_COUNT;
	do {
		ret = pci_read_config_dword(pdev, PUNIT_MAILBOX_INTERFACE,
					    &data);
		if (ret)
			return ret;

		if (data & BIT_ULL(PUNIT_MAILBOX_BUSY_BIT)) {
			ret = -EBUSY;
			continue;
		}
		ret = 0;
		break;
	} while (--retries);

	if (ret)
		return ret;

	/* Write DATA register */
	ret = pci_write_config_dword(pdev, PUNIT_MAILBOX_DATA,
				     mbox_cmd->req_data);
	if (ret)
		return ret;

	/* Write command register */
	data = BIT_ULL(PUNIT_MAILBOX_BUSY_BIT) |
		      (mbox_cmd->parameter & GENMASK_ULL(13, 0)) << 16 |
		      (mbox_cmd->sub_command << 8) |
		      mbox_cmd->command;

	ret = pci_write_config_dword(pdev, PUNIT_MAILBOX_INTERFACE, data);
	if (ret)
		return ret;

	/* Poll for rb bit == 0 */
	retries = OS_MAILBOX_RETRY_COUNT;
	do {
		ret = pci_read_config_dword(pdev, PUNIT_MAILBOX_INTERFACE,
					    &data);
		if (ret)
			return ret;

		if (data & BIT_ULL(PUNIT_MAILBOX_BUSY_BIT)) {
			ret = -EBUSY;
			continue;
		}

		if (data & 0xff)
			return -ENXIO;

		ret = pci_read_config_dword(pdev, PUNIT_MAILBOX_DATA, &data);
		if (ret)
			return ret;

		mbox_cmd->resp_data = data;
		ret = 0;
		break;
	} while (--retries);

	return ret;
}