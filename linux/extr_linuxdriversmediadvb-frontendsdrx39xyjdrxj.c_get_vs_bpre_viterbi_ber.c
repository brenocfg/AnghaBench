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
typedef  int u16 ;
struct i2c_device_addr {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int SYMBOLS_PER_SEGMENT ; 
 int VSB_TOP_MEASUREMENT_PERIOD ; 
 int /*<<< orphan*/  VSB_TOP_NR_SYM_ERRS__A ; 
 int drxj_dap_read_reg16 (struct i2c_device_addr*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static int get_vs_bpre_viterbi_ber(struct i2c_device_addr *dev_addr,
				   u32 *ber, u32 *cnt)
{
	u16 data = 0;
	int rc;

	rc = drxj_dap_read_reg16(dev_addr, VSB_TOP_NR_SYM_ERRS__A, &data, 0);
	if (rc != 0) {
		pr_err("error %d\n", rc);
		return -EIO;
	}
	*ber = data;
	*cnt = VSB_TOP_MEASUREMENT_PERIOD * SYMBOLS_PER_SEGMENT;

	return 0;
}