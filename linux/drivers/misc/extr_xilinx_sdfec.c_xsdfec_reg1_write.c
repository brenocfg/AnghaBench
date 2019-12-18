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
 scalar_t__ XSDFEC_LDPC_CODE_REG1_ADDR_BASE ; 
 scalar_t__ XSDFEC_LDPC_CODE_REG1_ADDR_HIGH ; 
 int XSDFEC_LDPC_REG_JUMP ; 
 int XSDFEC_REG1_NM_LSB ; 
 int XSDFEC_REG1_NM_MASK ; 
 int XSDFEC_REG1_NO_PACKING_LSB ; 
 int XSDFEC_REG1_NO_PACKING_MASK ; 
 int XSDFEC_REG1_PSIZE_MAX ; 
 int XSDFEC_REG1_PSIZE_MIN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  xsdfec_regwrite (struct xsdfec_dev*,scalar_t__,int) ; 

__attribute__((used)) static int xsdfec_reg1_write(struct xsdfec_dev *xsdfec, u32 psize,
			     u32 no_packing, u32 nm, u32 offset)
{
	u32 wdata;

	if (psize < XSDFEC_REG1_PSIZE_MIN || psize > XSDFEC_REG1_PSIZE_MAX) {
		dev_dbg(xsdfec->dev, "Psize is not in range");
		return -EINVAL;
	}

	if (no_packing != 0 && no_packing != 1)
		dev_dbg(xsdfec->dev, "No-packing bit register invalid");
	no_packing = ((no_packing << XSDFEC_REG1_NO_PACKING_LSB) &
		      XSDFEC_REG1_NO_PACKING_MASK);

	if (nm & ~(XSDFEC_REG1_NM_MASK >> XSDFEC_REG1_NM_LSB))
		dev_dbg(xsdfec->dev, "NM is beyond 10 bits");
	nm = (nm << XSDFEC_REG1_NM_LSB) & XSDFEC_REG1_NM_MASK;

	wdata = nm | no_packing | psize;
	if (XSDFEC_LDPC_CODE_REG1_ADDR_BASE + (offset * XSDFEC_LDPC_REG_JUMP) >
	    XSDFEC_LDPC_CODE_REG1_ADDR_HIGH) {
		dev_dbg(xsdfec->dev, "Writing outside of LDPC reg1 space 0x%x",
			XSDFEC_LDPC_CODE_REG1_ADDR_BASE +
				(offset * XSDFEC_LDPC_REG_JUMP));
		return -EINVAL;
	}
	xsdfec_regwrite(xsdfec,
			XSDFEC_LDPC_CODE_REG1_ADDR_BASE +
				(offset * XSDFEC_LDPC_REG_JUMP),
			wdata);
	return 0;
}