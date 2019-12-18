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
struct lan743x_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OTP_CMD_GO ; 
 int /*<<< orphan*/  OTP_CMD_GO_GO_ ; 
 int /*<<< orphan*/  OTP_FUNC_CMD ; 
 int /*<<< orphan*/  OTP_FUNC_CMD_READ_ ; 
 int /*<<< orphan*/  lan743x_csr_write (struct lan743x_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lan743x_otp_read_go(struct lan743x_adapter *adapter)
{
	lan743x_csr_write(adapter, OTP_FUNC_CMD, OTP_FUNC_CMD_READ_);
	lan743x_csr_write(adapter, OTP_CMD_GO, OTP_CMD_GO_GO_);
}