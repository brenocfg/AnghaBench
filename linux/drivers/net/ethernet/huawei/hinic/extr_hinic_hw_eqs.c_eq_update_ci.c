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
struct hinic_eq {int /*<<< orphan*/  hwif; int /*<<< orphan*/  wrapped; int /*<<< orphan*/  cons_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  EQ_ARMED ; 
 int EQ_CONS_IDX_REG_ADDR (struct hinic_eq*) ; 
 int HINIC_EQ_CI_CLEAR (int,int /*<<< orphan*/ ) ; 
 int HINIC_EQ_CI_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDX ; 
 int /*<<< orphan*/  INT_ARMED ; 
 int /*<<< orphan*/  WRAPPED ; 
 int /*<<< orphan*/  XOR_CHKSUM ; 
 int /*<<< orphan*/  eq_cons_idx_checksum_set (int) ; 
 int hinic_hwif_read_reg (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hinic_hwif_write_reg (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void eq_update_ci(struct hinic_eq *eq)
{
	u32 val, addr = EQ_CONS_IDX_REG_ADDR(eq);

	/* Read Modify Write */
	val = hinic_hwif_read_reg(eq->hwif, addr);

	val = HINIC_EQ_CI_CLEAR(val, IDX)       &
	      HINIC_EQ_CI_CLEAR(val, WRAPPED)   &
	      HINIC_EQ_CI_CLEAR(val, INT_ARMED) &
	      HINIC_EQ_CI_CLEAR(val, XOR_CHKSUM);

	val |= HINIC_EQ_CI_SET(eq->cons_idx, IDX)    |
	       HINIC_EQ_CI_SET(eq->wrapped, WRAPPED) |
	       HINIC_EQ_CI_SET(EQ_ARMED, INT_ARMED);

	val |= HINIC_EQ_CI_SET(eq_cons_idx_checksum_set(val), XOR_CHKSUM);

	hinic_hwif_write_reg(eq->hwif, addr, val);
}