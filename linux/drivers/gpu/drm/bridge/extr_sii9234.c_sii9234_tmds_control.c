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
struct sii9234 {int dummy; } ;

/* Variables and functions */
 int BIT_TMDS_CCTRL_TMDS_OE ; 
 int MHL_HPD_OUT_OVR_EN ; 
 int MHL_HPD_OUT_OVR_VAL ; 
 int /*<<< orphan*/  MHL_TX_INT_CTRL_REG ; 
 int /*<<< orphan*/  MHL_TX_TMDS_CCTRL ; 
 int /*<<< orphan*/  mhl_tx_writebm (struct sii9234*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sii9234_clear_error (struct sii9234*) ; 

__attribute__((used)) static u8 sii9234_tmds_control(struct sii9234 *ctx, bool enable)
{
	mhl_tx_writebm(ctx, MHL_TX_TMDS_CCTRL, enable ? ~0 : 0,
		       BIT_TMDS_CCTRL_TMDS_OE);
	mhl_tx_writebm(ctx, MHL_TX_INT_CTRL_REG, enable ? ~0 : 0,
		       MHL_HPD_OUT_OVR_EN | MHL_HPD_OUT_OVR_VAL);
	return sii9234_clear_error(ctx);
}