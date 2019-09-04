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
typedef  int u16 ;
struct ql3_adapter {size_t mac_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  PETBI_CONTROL_REG ; 
 int PETBI_CTRL_AUTO_NEG ; 
 int PETBI_CTRL_FULL_DUPLEX ; 
 int PETBI_CTRL_RESTART_NEG ; 
 int PETBI_CTRL_SPEED_1000 ; 
 int /*<<< orphan*/  PETBI_NEG_ADVER ; 
 int PETBI_NEG_DUPLEX ; 
 int PETBI_NEG_PAUSE ; 
 int PETBI_TBI_AUTO_SENSE ; 
 int /*<<< orphan*/  PETBI_TBI_CTRL ; 
 int /*<<< orphan*/ * PHYAddr ; 
 int /*<<< orphan*/  ql_mii_read_reg_ex (struct ql3_adapter*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_mii_write_reg_ex (struct ql3_adapter*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ql_petbi_start_neg_ex(struct ql3_adapter *qdev)
{
	u16 reg;

	/* Enable Auto-negotiation sense */
	ql_mii_read_reg_ex(qdev, PETBI_TBI_CTRL, &reg,
			   PHYAddr[qdev->mac_index]);
	reg |= PETBI_TBI_AUTO_SENSE;
	ql_mii_write_reg_ex(qdev, PETBI_TBI_CTRL, reg,
			    PHYAddr[qdev->mac_index]);

	ql_mii_write_reg_ex(qdev, PETBI_NEG_ADVER,
			    PETBI_NEG_PAUSE | PETBI_NEG_DUPLEX,
			    PHYAddr[qdev->mac_index]);

	ql_mii_write_reg_ex(qdev, PETBI_CONTROL_REG,
			    PETBI_CTRL_AUTO_NEG | PETBI_CTRL_RESTART_NEG |
			    PETBI_CTRL_FULL_DUPLEX | PETBI_CTRL_SPEED_1000,
			    PHYAddr[qdev->mac_index]);
}