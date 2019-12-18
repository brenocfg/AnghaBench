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
struct ucc_slow_private {scalar_t__ enabled_rx; scalar_t__ enabled_tx; struct ucc_slow* us_regs; } ;
struct ucc_slow {int /*<<< orphan*/  gumr_l; } ;
typedef  enum comm_dir { ____Placeholder_comm_dir } comm_dir ;

/* Variables and functions */
 int COMM_DIR_RX ; 
 int COMM_DIR_TX ; 
 int /*<<< orphan*/  UCC_SLOW_GUMR_L_ENR ; 
 int /*<<< orphan*/  UCC_SLOW_GUMR_L_ENT ; 
 int /*<<< orphan*/  in_be32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  out_be32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void ucc_slow_disable(struct ucc_slow_private * uccs, enum comm_dir mode)
{
	struct ucc_slow *us_regs;
	u32 gumr_l;

	us_regs = uccs->us_regs;

	/* Disable reception and/or transmission on this UCC. */
	gumr_l = in_be32(&us_regs->gumr_l);
	if (mode & COMM_DIR_TX) {
		gumr_l &= ~UCC_SLOW_GUMR_L_ENT;
		uccs->enabled_tx = 0;
	}
	if (mode & COMM_DIR_RX) {
		gumr_l &= ~UCC_SLOW_GUMR_L_ENR;
		uccs->enabled_rx = 0;
	}
	out_be32(&us_regs->gumr_l, gumr_l);
}