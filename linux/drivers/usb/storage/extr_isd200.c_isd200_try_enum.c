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
struct us_data {scalar_t__ extra; } ;
struct isd200_info {unsigned char* RegsBuf; unsigned char DeviceHead; int /*<<< orphan*/  DeviceFlags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACTION_ENUM ; 
 int /*<<< orphan*/  ACTION_READ_STATUS ; 
 unsigned char ATA_ADDRESS_DEVHEAD_SLAVE ; 
 unsigned char ATA_ADDRESS_DEVHEAD_STD ; 
 unsigned char ATA_BUSY ; 
 unsigned char ATA_DF ; 
 unsigned char ATA_DRDY ; 
 unsigned char ATA_ERR ; 
 size_t ATA_REG_HCYL_OFFSET ; 
 size_t ATA_REG_LCYL_OFFSET ; 
 size_t ATA_REG_STATUS_OFFSET ; 
 int /*<<< orphan*/  DF_ATA_DEVICE ; 
 unsigned long HZ ; 
 unsigned long ISD200_ENUM_BSY_TIMEOUT ; 
 unsigned long ISD200_ENUM_DETECT_TIMEOUT ; 
 int ISD200_GOOD ; 
 int isd200_action (struct us_data*,int /*<<< orphan*/ ,unsigned char*,int) ; 
 int isd200_atapi_soft_reset (struct us_data*) ; 
 unsigned long jiffies ; 
 scalar_t__ time_after_eq (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  usb_stor_dbg (struct us_data*,char*,...) ; 

__attribute__((used)) static int isd200_try_enum(struct us_data *us, unsigned char master_slave,
			   int detect )
{
	int status = ISD200_GOOD;
	unsigned long endTime;
	struct isd200_info *info = (struct isd200_info *)us->extra;
	unsigned char *regs = info->RegsBuf;
	int recheckAsMaster = 0;

	if ( detect )
		endTime = jiffies + ISD200_ENUM_DETECT_TIMEOUT * HZ;
	else
		endTime = jiffies + ISD200_ENUM_BSY_TIMEOUT * HZ;

	/* loop until we detect !BSY or timeout */
	while(1) {

		status = isd200_action( us, ACTION_ENUM, NULL, master_slave );
		if ( status != ISD200_GOOD )
			break;

		status = isd200_action( us, ACTION_READ_STATUS, 
					regs, 8 );
		if ( status != ISD200_GOOD )
			break;

		if (!detect) {
			if (regs[ATA_REG_STATUS_OFFSET] & ATA_BUSY) {
				usb_stor_dbg(us, "   %s status is still BSY, try again...\n",
					     master_slave == ATA_ADDRESS_DEVHEAD_STD ?
					     "Master" : "Slave");
			} else {
				usb_stor_dbg(us, "   %s status !BSY, continue with next operation\n",
					     master_slave == ATA_ADDRESS_DEVHEAD_STD ?
					     "Master" : "Slave");
				break;
			}
		}
		/* check for ATA_BUSY and */
		/* ATA_DF (workaround ATA Zip drive) and */
		/* ATA_ERR (workaround for Archos CD-ROM) */
		else if (regs[ATA_REG_STATUS_OFFSET] &
			 (ATA_BUSY | ATA_DF | ATA_ERR)) {
			usb_stor_dbg(us, "   Status indicates it is not ready, try again...\n");
		}
		/* check for DRDY, ATA devices set DRDY after SRST */
		else if (regs[ATA_REG_STATUS_OFFSET] & ATA_DRDY) {
			usb_stor_dbg(us, "   Identified ATA device\n");
			info->DeviceFlags |= DF_ATA_DEVICE;
			info->DeviceHead = master_slave;
			break;
		} 
		/*
		 * check Cylinder High/Low to
		 * determine if it is an ATAPI device
		 */
		else if (regs[ATA_REG_HCYL_OFFSET] == 0xEB &&
			 regs[ATA_REG_LCYL_OFFSET] == 0x14) {
			/*
			 * It seems that the RICOH
			 * MP6200A CD/RW drive will
			 * report itself okay as a
			 * slave when it is really a
			 * master. So this check again
			 * as a master device just to
			 * make sure it doesn't report
			 * itself okay as a master also
			 */
			if ((master_slave & ATA_ADDRESS_DEVHEAD_SLAVE) &&
			    !recheckAsMaster) {
				usb_stor_dbg(us, "   Identified ATAPI device as slave.  Rechecking again as master\n");
				recheckAsMaster = 1;
				master_slave = ATA_ADDRESS_DEVHEAD_STD;
			} else {
				usb_stor_dbg(us, "   Identified ATAPI device\n");
				info->DeviceHead = master_slave;
			      
				status = isd200_atapi_soft_reset(us);
				break;
			}
		} else {
			usb_stor_dbg(us, "   Not ATA, not ATAPI - Weird\n");
			break;
		}

		/* check for timeout on this request */
		if (time_after_eq(jiffies, endTime)) {
			if (!detect)
				usb_stor_dbg(us, "   BSY check timeout, just continue with next operation...\n");
			else
				usb_stor_dbg(us, "   Device detect timeout!\n");
			break;
		}
	}

	return status;
}