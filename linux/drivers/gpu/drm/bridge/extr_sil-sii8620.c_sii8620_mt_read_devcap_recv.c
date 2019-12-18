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
typedef  int u8 ;
struct sii8620_mt_msg {scalar_t__* reg; } ;
struct sii8620 {int dummy; } ;

/* Variables and functions */
 int BIT_EDID_CTRL_DEVCAP_SELECT_DEVCAP ; 
 int BIT_EDID_CTRL_EDID_FIFO_ADDR_AUTO ; 
 int BIT_EDID_CTRL_EDID_MODE_EN ; 
 int BIT_EDID_CTRL_XDEVCAP_EN ; 
 int BIT_INTR9_DEVCAP_DONE ; 
 int BIT_INTR9_EDID_DONE ; 
 int BIT_INTR9_EDID_ERROR ; 
 scalar_t__ MHL_READ_XDEVCAP ; 
 int /*<<< orphan*/  REG_EDID_CTRL ; 
 int /*<<< orphan*/  REG_EDID_FIFO_ADDR ; 
 int /*<<< orphan*/  REG_INTR9_MASK ; 
 int /*<<< orphan*/  sii8620_mr_devcap (struct sii8620*) ; 
 int /*<<< orphan*/  sii8620_mr_xdevcap (struct sii8620*) ; 
 int /*<<< orphan*/  sii8620_write_seq (struct sii8620*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sii8620_mt_read_devcap_recv(struct sii8620 *ctx,
					struct sii8620_mt_msg *msg)
{
	u8 ctrl = BIT_EDID_CTRL_DEVCAP_SELECT_DEVCAP
		| BIT_EDID_CTRL_EDID_FIFO_ADDR_AUTO
		| BIT_EDID_CTRL_EDID_MODE_EN;

	if (msg->reg[0] == MHL_READ_XDEVCAP)
		ctrl |= BIT_EDID_CTRL_XDEVCAP_EN;

	sii8620_write_seq(ctx,
		REG_INTR9_MASK, BIT_INTR9_DEVCAP_DONE | BIT_INTR9_EDID_DONE
			| BIT_INTR9_EDID_ERROR,
		REG_EDID_CTRL, ctrl,
		REG_EDID_FIFO_ADDR, 0
	);

	if (msg->reg[0] == MHL_READ_XDEVCAP)
		sii8620_mr_xdevcap(ctx);
	else
		sii8620_mr_devcap(ctx);
}