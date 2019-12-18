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
struct us_data {int max_lun; struct rts51x_chip* extra; int /*<<< orphan*/  extra_destructor; } ;
struct rts51x_status {int dummy; } ;
struct rts51x_chip {int max_lun; int flag; struct rts51x_chip* status; struct us_data* us; } ;

/* Variables and functions */
 scalar_t__ CHECK_FW_VER (struct rts51x_chip*,int) ; 
 scalar_t__ CHECK_PID (struct rts51x_chip*,int) ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SET_AUTO_DELINK (struct rts51x_chip*) ; 
 int STATUS_LEN (struct rts51x_chip*) ; 
 scalar_t__ SUPPORT_AUTO_DELINK (struct rts51x_chip*) ; 
 int /*<<< orphan*/  config_autodelink_after_power_on (struct us_data*) ; 
 int /*<<< orphan*/  kfree (struct rts51x_chip*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  realtek_cr_autosuspend_setup (struct us_data*) ; 
 int /*<<< orphan*/  realtek_cr_destructor ; 
 int rts51x_check_status (struct us_data*,int /*<<< orphan*/ ) ; 
 int rts51x_get_max_lun (struct us_data*) ; 
 scalar_t__ ss_en ; 
 int /*<<< orphan*/  usb_stor_dbg (struct us_data*,char*,int) ; 

__attribute__((used)) static int init_realtek_cr(struct us_data *us)
{
	struct rts51x_chip *chip;
	int size, i, retval;

	chip = kzalloc(sizeof(struct rts51x_chip), GFP_KERNEL);
	if (!chip)
		return -ENOMEM;

	us->extra = chip;
	us->extra_destructor = realtek_cr_destructor;
	us->max_lun = chip->max_lun = rts51x_get_max_lun(us);
	chip->us = us;

	usb_stor_dbg(us, "chip->max_lun = %d\n", chip->max_lun);

	size = (chip->max_lun + 1) * sizeof(struct rts51x_status);
	chip->status = kzalloc(size, GFP_KERNEL);
	if (!chip->status)
		goto INIT_FAIL;

	for (i = 0; i <= (int)(chip->max_lun); i++) {
		retval = rts51x_check_status(us, (u8) i);
		if (retval < 0)
			goto INIT_FAIL;
	}

	if (CHECK_PID(chip, 0x0138) || CHECK_PID(chip, 0x0158) ||
	    CHECK_PID(chip, 0x0159)) {
		if (CHECK_FW_VER(chip, 0x5888) || CHECK_FW_VER(chip, 0x5889) ||
				CHECK_FW_VER(chip, 0x5901))
			SET_AUTO_DELINK(chip);
		if (STATUS_LEN(chip) == 16) {
			if (SUPPORT_AUTO_DELINK(chip))
				SET_AUTO_DELINK(chip);
		}
	}
#ifdef CONFIG_REALTEK_AUTOPM
	if (ss_en)
		realtek_cr_autosuspend_setup(us);
#endif

	usb_stor_dbg(us, "chip->flag = 0x%x\n", chip->flag);

	(void)config_autodelink_after_power_on(us);

	return 0;

INIT_FAIL:
	if (us->extra) {
		kfree(chip->status);
		kfree(us->extra);
		us->extra = NULL;
	}

	return -EIO;
}