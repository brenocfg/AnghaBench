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
typedef  int u64 ;
typedef  int u32 ;
struct tg3 {int /*<<< orphan*/ * fw_ver; } ;

/* Variables and functions */
 scalar_t__ ASIC_REV_5762 ; 
 scalar_t__ OTP_ADDRESS_MAGIC0 ; 
 scalar_t__ TG3_OTP_MAGIC0_VALID (int) ; 
 scalar_t__ TG3_VER_SIZE ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ *,scalar_t__,char*,int) ; 
 int strlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tg3_ape_otp_read (struct tg3*,scalar_t__,int*) ; 
 scalar_t__ tg3_asic_rev (struct tg3*) ; 

__attribute__((used)) static void tg3_read_otp_ver(struct tg3 *tp)
{
	u32 val, val2;

	if (tg3_asic_rev(tp) != ASIC_REV_5762)
		return;

	if (!tg3_ape_otp_read(tp, OTP_ADDRESS_MAGIC0, &val) &&
	    !tg3_ape_otp_read(tp, OTP_ADDRESS_MAGIC0 + 4, &val2) &&
	    TG3_OTP_MAGIC0_VALID(val)) {
		u64 val64 = (u64) val << 32 | val2;
		u32 ver = 0;
		int i, vlen;

		for (i = 0; i < 7; i++) {
			if ((val64 & 0xff) == 0)
				break;
			ver = val64 & 0xff;
			val64 >>= 8;
		}
		vlen = strlen(tp->fw_ver);
		snprintf(&tp->fw_ver[vlen], TG3_VER_SIZE - vlen, " .%02d", ver);
	}
}