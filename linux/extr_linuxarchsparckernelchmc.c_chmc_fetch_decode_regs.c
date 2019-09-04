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
struct chmc {scalar_t__ layout_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHMCTRL_DECODE1 ; 
 int /*<<< orphan*/  CHMCTRL_DECODE2 ; 
 int /*<<< orphan*/  CHMCTRL_DECODE3 ; 
 int /*<<< orphan*/  CHMCTRL_DECODE4 ; 
 int /*<<< orphan*/  chmc_interpret_one_decode_reg (struct chmc*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chmc_read_mcreg (struct chmc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void chmc_fetch_decode_regs(struct chmc *p)
{
	if (p->layout_size == 0)
		return;

	chmc_interpret_one_decode_reg(p, 0,
				      chmc_read_mcreg(p, CHMCTRL_DECODE1));
	chmc_interpret_one_decode_reg(p, 1,
				      chmc_read_mcreg(p, CHMCTRL_DECODE2));
	chmc_interpret_one_decode_reg(p, 2,
				      chmc_read_mcreg(p, CHMCTRL_DECODE3));
	chmc_interpret_one_decode_reg(p, 3,
				      chmc_read_mcreg(p, CHMCTRL_DECODE4));
}