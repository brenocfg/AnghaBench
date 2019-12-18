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
struct xsdfec_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ XSDFEC_LDPC_CODE_REG0_ADDR_BASE ; 
 scalar_t__ XSDFEC_LDPC_CODE_REG0_ADDR_HIGH ; 
 int XSDFEC_LDPC_REG_JUMP ; 
 int XSDFEC_REG0_K_LSB ; 
 int XSDFEC_REG0_K_MAX ; 
 int XSDFEC_REG0_K_MIN ; 
 int XSDFEC_REG0_K_MUL_P ; 
 int XSDFEC_REG0_N_LSB ; 
 int XSDFEC_REG0_N_MAX ; 
 int XSDFEC_REG0_N_MIN ; 
 int XSDFEC_REG0_N_MUL_P ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  xsdfec_regwrite (struct xsdfec_dev*,scalar_t__,int) ; 

__attribute__((used)) static int xsdfec_reg0_write(struct xsdfec_dev *xsdfec, u32 n, u32 k, u32 psize,
			     u32 offset)
{
	u32 wdata;

	if (n < XSDFEC_REG0_N_MIN || n > XSDFEC_REG0_N_MAX || psize == 0 ||
	    (n > XSDFEC_REG0_N_MUL_P * psize) || n <= k || ((n % psize) != 0)) {
		dev_dbg(xsdfec->dev, "N value is not in range");
		return -EINVAL;
	}
	n <<= XSDFEC_REG0_N_LSB;

	if (k < XSDFEC_REG0_K_MIN || k > XSDFEC_REG0_K_MAX ||
	    (k > XSDFEC_REG0_K_MUL_P * psize) || ((k % psize) != 0)) {
		dev_dbg(xsdfec->dev, "K value is not in range");
		return -EINVAL;
	}
	k = k << XSDFEC_REG0_K_LSB;
	wdata = k | n;

	if (XSDFEC_LDPC_CODE_REG0_ADDR_BASE + (offset * XSDFEC_LDPC_REG_JUMP) >
	    XSDFEC_LDPC_CODE_REG0_ADDR_HIGH) {
		dev_dbg(xsdfec->dev, "Writing outside of LDPC reg0 space 0x%x",
			XSDFEC_LDPC_CODE_REG0_ADDR_BASE +
				(offset * XSDFEC_LDPC_REG_JUMP));
		return -EINVAL;
	}
	xsdfec_regwrite(xsdfec,
			XSDFEC_LDPC_CODE_REG0_ADDR_BASE +
				(offset * XSDFEC_LDPC_REG_JUMP),
			wdata);
	return 0;
}