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
typedef  scalar_t__ u32 ;
struct lan743x_adapter {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MAX_OTP_SIZE ; 
 int /*<<< orphan*/  OTP_CMD_GO ; 
 int /*<<< orphan*/  OTP_CMD_GO_GO_ ; 
 int /*<<< orphan*/  OTP_PRGM_DATA ; 
 int /*<<< orphan*/  OTP_PRGM_MODE ; 
 int /*<<< orphan*/  OTP_PRGM_MODE_BYTE_ ; 
 int /*<<< orphan*/  OTP_TST_CMD ; 
 int /*<<< orphan*/  OTP_TST_CMD_PRGVRFY_ ; 
 int /*<<< orphan*/  lan743x_csr_write (struct lan743x_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lan743x_otp_power_down (struct lan743x_adapter*) ; 
 int lan743x_otp_power_up (struct lan743x_adapter*) ; 
 int /*<<< orphan*/  lan743x_otp_set_address (struct lan743x_adapter*,scalar_t__) ; 
 int lan743x_otp_wait_till_not_busy (struct lan743x_adapter*) ; 

__attribute__((used)) static int lan743x_otp_write(struct lan743x_adapter *adapter, u32 offset,
			     u32 length, u8 *data)
{
	int ret;
	int i;

	if (offset + length > MAX_OTP_SIZE)
		return -EINVAL;

	ret = lan743x_otp_power_up(adapter);
	if (ret < 0)
		return ret;

	ret = lan743x_otp_wait_till_not_busy(adapter);
	if (ret < 0)
		return ret;

	/* set to BYTE program mode */
	lan743x_csr_write(adapter, OTP_PRGM_MODE, OTP_PRGM_MODE_BYTE_);

	for (i = 0; i < length; i++) {
		lan743x_otp_set_address(adapter, offset + i);

		lan743x_csr_write(adapter, OTP_PRGM_DATA, data[i]);
		lan743x_csr_write(adapter, OTP_TST_CMD, OTP_TST_CMD_PRGVRFY_);
		lan743x_csr_write(adapter, OTP_CMD_GO, OTP_CMD_GO_GO_);

		ret = lan743x_otp_wait_till_not_busy(adapter);
		if (ret < 0)
			return ret;
	}

	lan743x_otp_power_down(adapter);

	return 0;
}