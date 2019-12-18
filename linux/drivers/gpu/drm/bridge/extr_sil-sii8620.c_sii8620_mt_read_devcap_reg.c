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
struct sii8620_mt_msg {int* reg; int /*<<< orphan*/  recv; int /*<<< orphan*/  send; } ;
struct sii8620 {int dummy; } ;

/* Variables and functions */
 int MHL_READ_DEVCAP_REG ; 
 int MHL_READ_XDEVCAP_REG ; 
 int /*<<< orphan*/  sii8620_mt_msc_cmd_send ; 
 struct sii8620_mt_msg* sii8620_mt_msg_new (struct sii8620*) ; 
 int /*<<< orphan*/  sii8620_mt_read_devcap_reg_recv ; 

__attribute__((used)) static void sii8620_mt_read_devcap_reg(struct sii8620 *ctx, u8 reg)
{
	struct sii8620_mt_msg *msg = sii8620_mt_msg_new(ctx);

	if (!msg)
		return;

	msg->reg[0] = (reg & 0x80) ? MHL_READ_XDEVCAP_REG : MHL_READ_DEVCAP_REG;
	msg->reg[1] = reg;
	msg->send = sii8620_mt_msc_cmd_send;
	msg->recv = sii8620_mt_read_devcap_reg_recv;
}