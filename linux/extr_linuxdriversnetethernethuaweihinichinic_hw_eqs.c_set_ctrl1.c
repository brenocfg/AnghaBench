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
struct hinic_eq {int type; int q_len; int /*<<< orphan*/  hwif; int /*<<< orphan*/  q_id; } ;
typedef  enum hinic_eq_type { ____Placeholder_hinic_eq_type } hinic_eq_type ;

/* Variables and functions */
 int /*<<< orphan*/  ELEM_SIZE ; 
 int EQ_SET_HW_ELEM_SIZE_VAL (struct hinic_eq*) ; 
 int EQ_SET_HW_PAGE_SIZE_VAL (struct hinic_eq*) ; 
 int HINIC_AEQ ; 
 int HINIC_AEQ_CTRL_1_CLEAR (int,int /*<<< orphan*/ ) ; 
 int HINIC_AEQ_CTRL_1_SET (int,int /*<<< orphan*/ ) ; 
 int HINIC_CEQ ; 
 int HINIC_CEQ_CTRL_1_CLEAR (int,int /*<<< orphan*/ ) ; 
 int HINIC_CEQ_CTRL_1_SET (int,int /*<<< orphan*/ ) ; 
 int HINIC_CSR_AEQ_CTRL_1_ADDR (int /*<<< orphan*/ ) ; 
 int HINIC_CSR_CEQ_CTRL_1_ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LEN ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int hinic_hwif_read_reg (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hinic_hwif_write_reg (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void set_ctrl1(struct hinic_eq *eq)
{
	enum hinic_eq_type type = eq->type;
	u32 page_size_val, elem_size;
	u32 addr, val, ctrl1;

	if (type == HINIC_AEQ) {
		/* RMW Ctrl1 */
		addr = HINIC_CSR_AEQ_CTRL_1_ADDR(eq->q_id);

		page_size_val = EQ_SET_HW_PAGE_SIZE_VAL(eq);
		elem_size = EQ_SET_HW_ELEM_SIZE_VAL(eq);

		val = hinic_hwif_read_reg(eq->hwif, addr);

		val = HINIC_AEQ_CTRL_1_CLEAR(val, LEN)          &
		      HINIC_AEQ_CTRL_1_CLEAR(val, ELEM_SIZE)    &
		      HINIC_AEQ_CTRL_1_CLEAR(val, PAGE_SIZE);

		ctrl1 = HINIC_AEQ_CTRL_1_SET(eq->q_len, LEN)            |
			HINIC_AEQ_CTRL_1_SET(elem_size, ELEM_SIZE)      |
			HINIC_AEQ_CTRL_1_SET(page_size_val, PAGE_SIZE);

		val |= ctrl1;

		hinic_hwif_write_reg(eq->hwif, addr, val);
	} else if (type == HINIC_CEQ) {
		/* RMW Ctrl1 */
		addr = HINIC_CSR_CEQ_CTRL_1_ADDR(eq->q_id);

		page_size_val = EQ_SET_HW_PAGE_SIZE_VAL(eq);

		val = hinic_hwif_read_reg(eq->hwif, addr);

		val = HINIC_CEQ_CTRL_1_CLEAR(val, LEN) &
		      HINIC_CEQ_CTRL_1_CLEAR(val, PAGE_SIZE);

		ctrl1 = HINIC_CEQ_CTRL_1_SET(eq->q_len, LEN) |
			HINIC_CEQ_CTRL_1_SET(page_size_val, PAGE_SIZE);

		val |= ctrl1;

		hinic_hwif_write_reg(eq->hwif, addr, val);
	}
}