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
struct mxic_nand_ctlr {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ IDLY_CODE (int) ; 
 int IDLY_CODE_VAL (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void mxic_nfc_set_input_delay(struct mxic_nand_ctlr *nfc, u8 idly_code)
{
	writel(IDLY_CODE_VAL(0, idly_code) |
	       IDLY_CODE_VAL(1, idly_code) |
	       IDLY_CODE_VAL(2, idly_code) |
	       IDLY_CODE_VAL(3, idly_code),
	       nfc->regs + IDLY_CODE(0));
	writel(IDLY_CODE_VAL(4, idly_code) |
	       IDLY_CODE_VAL(5, idly_code) |
	       IDLY_CODE_VAL(6, idly_code) |
	       IDLY_CODE_VAL(7, idly_code),
	       nfc->regs + IDLY_CODE(1));
}