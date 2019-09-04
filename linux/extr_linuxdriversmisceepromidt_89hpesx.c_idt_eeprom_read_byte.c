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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct idt_smb_seq {int ccode; int /*<<< orphan*/  bytecnt; int /*<<< orphan*/ * data; } ;
struct idt_eeprom_seq {int cmd; int /*<<< orphan*/  data; int /*<<< orphan*/  memaddr; int /*<<< orphan*/  eeaddr; } ;
struct idt_89hpesx_dev {int iniccode; int inieecmd; int (* smb_write ) (struct idt_89hpesx_dev*,struct idt_smb_seq*) ;int (* smb_read ) (struct idt_89hpesx_dev*,struct idt_smb_seq*) ;int /*<<< orphan*/  eeaddr; TYPE_1__* client; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int CCODE_EEPROM ; 
 int EEPROM_LAERR ; 
 int EEPROM_MSS ; 
 int EEPROM_NAERR ; 
 int EEPROM_OP_READ ; 
 int /*<<< orphan*/  EEPROM_RD_CNT ; 
 int /*<<< orphan*/  EEPROM_TOUT ; 
 int /*<<< orphan*/  EEPROM_WRRD_CNT ; 
 int EREMOTEIO ; 
 int RETRY_CNT ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int stub1 (struct idt_89hpesx_dev*,struct idt_smb_seq*) ; 
 int stub2 (struct idt_89hpesx_dev*,struct idt_smb_seq*) ; 

__attribute__((used)) static int idt_eeprom_read_byte(struct idt_89hpesx_dev *pdev, u16 memaddr,
				u8 *data)
{
	struct device *dev = &pdev->client->dev;
	struct idt_eeprom_seq eeseq;
	struct idt_smb_seq smbseq;
	int ret, retry;

	/* Initialize SMBus sequence fields */
	smbseq.ccode = pdev->iniccode | CCODE_EEPROM;
	smbseq.data = (u8 *)&eeseq;

	/*
	 * Sometimes EEPROM may respond with NACK if it's busy with previous
	 * operation, so we need to perform a few attempts of read cycle
	 */
	retry = RETRY_CNT;
	do {
		/* Send EEPROM memory address to read data from */
		smbseq.bytecnt = EEPROM_WRRD_CNT;
		eeseq.cmd = pdev->inieecmd | EEPROM_OP_READ;
		eeseq.eeaddr = pdev->eeaddr;
		eeseq.memaddr = cpu_to_le16(memaddr);
		ret = pdev->smb_write(pdev, &smbseq);
		if (ret != 0) {
			dev_err(dev, "Failed to init eeprom addr 0x%02hhx",
				memaddr);
			break;
		}

		/* Perform read operation */
		smbseq.bytecnt = EEPROM_RD_CNT;
		ret = pdev->smb_read(pdev, &smbseq);
		if (ret != 0) {
			dev_err(dev, "Failed to read eeprom data 0x%02hhx",
				memaddr);
			break;
		}

		/* Restart read operation if the device is busy */
		if (retry && (eeseq.cmd & EEPROM_NAERR)) {
			dev_dbg(dev, "EEPROM busy, retry reading after %d ms",
				EEPROM_TOUT);
			msleep(EEPROM_TOUT);
			continue;
		}

		/* Check whether IDT successfully read data from EEPROM */
		if (eeseq.cmd & (EEPROM_NAERR | EEPROM_LAERR | EEPROM_MSS)) {
			dev_err(dev,
				"Communication with eeprom failed, cmd 0x%hhx",
				eeseq.cmd);
			ret = -EREMOTEIO;
			break;
		}

		/* Save retrieved data and exit the loop */
		*data = eeseq.data;
		break;
	} while (retry--);

	/* Return the status of operation */
	return ret;
}