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
typedef  int u8 ;
typedef  int u16 ;
struct cec_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SECOCEC_DEVICE_LA ; 
 int /*<<< orphan*/  SECOCEC_ENABLE_REG_1 ; 
 int SECOCEC_ENABLE_REG_1_CEC ; 
 int smb_rd16 (int /*<<< orphan*/ ,int*) ; 
 int smb_wr16 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int secocec_adap_log_addr(struct cec_adapter *adap, u8 logical_addr)
{
	u16 enable_val = 0;
	int status;

	/* Disable device */
	status = smb_rd16(SECOCEC_ENABLE_REG_1, &enable_val);
	if (status)
		return status;

	status = smb_wr16(SECOCEC_ENABLE_REG_1,
			  enable_val & ~SECOCEC_ENABLE_REG_1_CEC);
	if (status)
		return status;

	/* Write logical address
	 * NOTE: CEC_LOG_ADDR_INVALID is mapped to the 'Unregistered' LA
	 */
	status = smb_wr16(SECOCEC_DEVICE_LA, logical_addr & 0xf);
	if (status)
		return status;

	/* Re-enable device */
	status = smb_wr16(SECOCEC_ENABLE_REG_1,
			  enable_val | SECOCEC_ENABLE_REG_1_CEC);
	if (status)
		return status;

	return 0;
}