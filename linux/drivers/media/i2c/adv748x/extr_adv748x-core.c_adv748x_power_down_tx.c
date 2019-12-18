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
struct adv748x_state {int dummy; } ;
struct adv748x_csi2 {int num_lanes; struct adv748x_state* state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADV748X_PAGE_TXA ; 
 int /*<<< orphan*/  ADV748X_PAGE_TXB ; 
 int /*<<< orphan*/  adv748x_write_check (struct adv748x_state*,int /*<<< orphan*/ ,int,int,int*) ; 
 scalar_t__ is_txa (struct adv748x_csi2*) ; 

__attribute__((used)) static int adv748x_power_down_tx(struct adv748x_csi2 *tx)
{
	struct adv748x_state *state = tx->state;
	u8 page = is_txa(tx) ? ADV748X_PAGE_TXA : ADV748X_PAGE_TXB;
	int ret = 0;

	/* ADI Required Writes */
	adv748x_write_check(state, page, 0x31, 0x82, &ret);
	adv748x_write_check(state, page, 0x1e, 0x00, &ret);

	/* Enable n-lane MIPI */
	adv748x_write_check(state, page, 0x00, 0x80 | tx->num_lanes, &ret);

	/* i2c_mipi_pll_en - 1'b1 */
	adv748x_write_check(state, page, 0xda, 0x01, &ret);

	/* ADI Required Write */
	adv748x_write_check(state, page, 0xc1, 0x3b, &ret);

	return ret;
}