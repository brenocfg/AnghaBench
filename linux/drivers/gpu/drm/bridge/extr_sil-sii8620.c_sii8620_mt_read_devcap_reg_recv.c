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
typedef  size_t u8 ;
struct sii8620_mt_msg {int* reg; int /*<<< orphan*/  ret; } ;
struct sii8620 {int /*<<< orphan*/ * devcap; int /*<<< orphan*/ * xdevcap; } ;

/* Variables and functions */

__attribute__((used)) static void sii8620_mt_read_devcap_reg_recv(struct sii8620 *ctx,
		struct sii8620_mt_msg *msg)
{
	u8 reg = msg->reg[1] & 0x7f;

	if (msg->reg[1] & 0x80)
		ctx->xdevcap[reg] = msg->ret;
	else
		ctx->devcap[reg] = msg->ret;
}