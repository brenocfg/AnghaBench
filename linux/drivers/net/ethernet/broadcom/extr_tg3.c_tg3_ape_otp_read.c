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
struct tg3 {int dummy; } ;

/* Variables and functions */
 int APE_OTP_ADDR_CPU_ENABLE ; 
 int APE_OTP_CTRL_CMD_RD ; 
 int APE_OTP_CTRL_PROG_EN ; 
 int APE_OTP_CTRL_START ; 
 int APE_OTP_STATUS_CMD_DONE ; 
 int EBUSY ; 
 int /*<<< orphan*/  TG3_APE_OTP_ADDR ; 
 int /*<<< orphan*/  TG3_APE_OTP_CTRL ; 
 int /*<<< orphan*/  TG3_APE_OTP_RD_DATA ; 
 int /*<<< orphan*/  TG3_APE_OTP_STATUS ; 
 int tg3_ape_read32 (struct tg3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tg3_ape_write32 (struct tg3*,int /*<<< orphan*/ ,int) ; 
 int tg3_nvram_lock (struct tg3*) ; 
 int /*<<< orphan*/  tg3_nvram_unlock (struct tg3*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int tg3_ape_otp_read(struct tg3 *tp, u32 offset, u32 *val)
{
	int i, err;
	u32 val2, off = offset * 8;

	err = tg3_nvram_lock(tp);
	if (err)
		return err;

	tg3_ape_write32(tp, TG3_APE_OTP_ADDR, off | APE_OTP_ADDR_CPU_ENABLE);
	tg3_ape_write32(tp, TG3_APE_OTP_CTRL, APE_OTP_CTRL_PROG_EN |
			APE_OTP_CTRL_CMD_RD | APE_OTP_CTRL_START);
	tg3_ape_read32(tp, TG3_APE_OTP_CTRL);
	udelay(10);

	for (i = 0; i < 100; i++) {
		val2 = tg3_ape_read32(tp, TG3_APE_OTP_STATUS);
		if (val2 & APE_OTP_STATUS_CMD_DONE) {
			*val = tg3_ape_read32(tp, TG3_APE_OTP_RD_DATA);
			break;
		}
		udelay(10);
	}

	tg3_ape_write32(tp, TG3_APE_OTP_CTRL, 0);

	tg3_nvram_unlock(tp);
	if (val2 & APE_OTP_STATUS_CMD_DONE)
		return 0;

	return -EBUSY;
}