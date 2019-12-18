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
 int /*<<< orphan*/  OTP_ADDR_HIGH ; 
 int /*<<< orphan*/  OTP_ADDR_LOW ; 
 int /*<<< orphan*/  lan743x_csr_write (struct lan743x_adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void lan743x_otp_set_address(struct lan743x_adapter *adapter,
				    u32 address)
{
	lan743x_csr_write(adapter, OTP_ADDR_HIGH, (address >> 8) & 0x03);
	lan743x_csr_write(adapter, OTP_ADDR_LOW, address & 0xFF);
}