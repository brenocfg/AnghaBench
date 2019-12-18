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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct myrb_hba {struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  dev_notice (int /*<<< orphan*/ *,char*,...) ; 

bool myrb_err_status(struct myrb_hba *cb, unsigned char error,
		unsigned char parm0, unsigned char parm1)
{
	struct pci_dev *pdev = cb->pdev;

	switch (error) {
	case 0x00:
		dev_info(&pdev->dev,
			 "Physical Device %d:%d Not Responding\n",
			 parm1, parm0);
		break;
	case 0x08:
		dev_notice(&pdev->dev, "Spinning Up Drives\n");
		break;
	case 0x30:
		dev_notice(&pdev->dev, "Configuration Checksum Error\n");
		break;
	case 0x60:
		dev_notice(&pdev->dev, "Mirror Race Recovery Failed\n");
		break;
	case 0x70:
		dev_notice(&pdev->dev, "Mirror Race Recovery In Progress\n");
		break;
	case 0x90:
		dev_notice(&pdev->dev, "Physical Device %d:%d COD Mismatch\n",
			   parm1, parm0);
		break;
	case 0xA0:
		dev_notice(&pdev->dev, "Logical Drive Installation Aborted\n");
		break;
	case 0xB0:
		dev_notice(&pdev->dev, "Mirror Race On A Critical Logical Drive\n");
		break;
	case 0xD0:
		dev_notice(&pdev->dev, "New Controller Configuration Found\n");
		break;
	case 0xF0:
		dev_err(&pdev->dev, "Fatal Memory Parity Error\n");
		return true;
	default:
		dev_err(&pdev->dev, "Unknown Initialization Error %02X\n",
			error);
		return true;
	}
	return false;
}