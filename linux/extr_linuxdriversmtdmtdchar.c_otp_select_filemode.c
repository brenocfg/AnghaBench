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
struct mtd_info {int dummy; } ;
struct mtd_file_info {int /*<<< orphan*/  mode; struct mtd_info* mtd; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  MTD_FILE_MODE_NORMAL ; 
 int /*<<< orphan*/  MTD_FILE_MODE_OTP_FACTORY ; 
 int /*<<< orphan*/  MTD_FILE_MODE_OTP_USER ; 
#define  MTD_OTP_FACTORY 130 
#define  MTD_OTP_OFF 129 
#define  MTD_OTP_USER 128 
 int mtd_read_fact_prot_reg (struct mtd_info*,int,int /*<<< orphan*/ ,size_t*,int /*<<< orphan*/ *) ; 
 int mtd_read_user_prot_reg (struct mtd_info*,int,int /*<<< orphan*/ ,size_t*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int otp_select_filemode(struct mtd_file_info *mfi, int mode)
{
	struct mtd_info *mtd = mfi->mtd;
	size_t retlen;

	switch (mode) {
	case MTD_OTP_FACTORY:
		if (mtd_read_fact_prot_reg(mtd, -1, 0, &retlen, NULL) ==
				-EOPNOTSUPP)
			return -EOPNOTSUPP;

		mfi->mode = MTD_FILE_MODE_OTP_FACTORY;
		break;
	case MTD_OTP_USER:
		if (mtd_read_user_prot_reg(mtd, -1, 0, &retlen, NULL) ==
				-EOPNOTSUPP)
			return -EOPNOTSUPP;

		mfi->mode = MTD_FILE_MODE_OTP_USER;
		break;
	case MTD_OTP_OFF:
		mfi->mode = MTD_FILE_MODE_NORMAL;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}