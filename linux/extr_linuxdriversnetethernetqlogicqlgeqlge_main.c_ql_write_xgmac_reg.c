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
typedef  int /*<<< orphan*/  u32 ;
struct ql_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XGMAC_ADDR ; 
 int /*<<< orphan*/  XGMAC_ADDR_RDY ; 
 int /*<<< orphan*/  XGMAC_ADDR_XME ; 
 int /*<<< orphan*/  XGMAC_DATA ; 
 int ql_wait_reg_rdy (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_write32 (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ql_write_xgmac_reg(struct ql_adapter *qdev, u32 reg, u32 data)
{
	int status;
	/* wait for reg to come ready */
	status = ql_wait_reg_rdy(qdev,
			XGMAC_ADDR, XGMAC_ADDR_RDY, XGMAC_ADDR_XME);
	if (status)
		return status;
	/* write the data to the data reg */
	ql_write32(qdev, XGMAC_DATA, data);
	/* trigger the write */
	ql_write32(qdev, XGMAC_ADDR, reg);
	return status;
}