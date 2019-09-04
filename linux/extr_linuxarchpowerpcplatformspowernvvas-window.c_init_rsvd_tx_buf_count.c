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
struct vas_window {int dummy; } ;
struct vas_winctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TX_RSVD_BUF_COUNT ; 
 int /*<<< orphan*/  VREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_hvwc_reg (struct vas_window*,int /*<<< orphan*/ ,unsigned long long) ; 

__attribute__((used)) static void init_rsvd_tx_buf_count(struct vas_window *txwin,
				struct vas_winctx *winctx)
{
	write_hvwc_reg(txwin, VREG(TX_RSVD_BUF_COUNT), 0ULL);
}