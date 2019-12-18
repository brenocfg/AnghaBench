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
typedef  size_t u8 ;
typedef  int u16 ;
struct us_data {scalar_t__ extra; } ;
struct rts51x_chip {int status_len; TYPE_2__* status; } ;
struct TYPE_3__ {size_t detailed_type1; } ;
struct TYPE_4__ {int vid; int pid; size_t cur_lun; size_t card_type; size_t total_lun; int fw_ver; size_t phy_exist; size_t multi_flag; size_t multi_card; size_t log_exist; size_t* function; TYPE_1__ detailed_type; } ;

/* Variables and functions */
 int EIO ; 
 int STATUS_SUCCESS ; 
 int rts51x_read_status (struct us_data*,size_t,size_t*,int,int*) ; 
 int /*<<< orphan*/  usb_stor_dbg (struct us_data*,char*,int) ; 

__attribute__((used)) static int rts51x_check_status(struct us_data *us, u8 lun)
{
	struct rts51x_chip *chip = (struct rts51x_chip *)(us->extra);
	int retval;
	u8 buf[16];

	retval = rts51x_read_status(us, lun, buf, 16, &(chip->status_len));
	if (retval != STATUS_SUCCESS)
		return -EIO;

	usb_stor_dbg(us, "chip->status_len = %d\n", chip->status_len);

	chip->status[lun].vid = ((u16) buf[0] << 8) | buf[1];
	chip->status[lun].pid = ((u16) buf[2] << 8) | buf[3];
	chip->status[lun].cur_lun = buf[4];
	chip->status[lun].card_type = buf[5];
	chip->status[lun].total_lun = buf[6];
	chip->status[lun].fw_ver = ((u16) buf[7] << 8) | buf[8];
	chip->status[lun].phy_exist = buf[9];
	chip->status[lun].multi_flag = buf[10];
	chip->status[lun].multi_card = buf[11];
	chip->status[lun].log_exist = buf[12];
	if (chip->status_len == 16) {
		chip->status[lun].detailed_type.detailed_type1 = buf[13];
		chip->status[lun].function[0] = buf[14];
		chip->status[lun].function[1] = buf[15];
	}

	return 0;
}