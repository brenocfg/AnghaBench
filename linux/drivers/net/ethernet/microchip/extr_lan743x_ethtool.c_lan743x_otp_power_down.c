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
struct lan743x_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OTP_PWR_DN ; 
 int OTP_PWR_DN_PWRDN_N_ ; 
 int lan743x_csr_read (struct lan743x_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lan743x_csr_write (struct lan743x_adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void lan743x_otp_power_down(struct lan743x_adapter *adapter)
{
	u32 reg_value;

	reg_value = lan743x_csr_read(adapter, OTP_PWR_DN);
	if (!(reg_value & OTP_PWR_DN_PWRDN_N_)) {
		/* set power down bit */
		reg_value |= OTP_PWR_DN_PWRDN_N_;
		lan743x_csr_write(adapter, OTP_PWR_DN, reg_value);
	}
}