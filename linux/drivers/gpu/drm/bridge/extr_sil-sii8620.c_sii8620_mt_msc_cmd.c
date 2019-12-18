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
typedef  void* u8 ;
struct sii8620_mt_msg {int /*<<< orphan*/  send; void** reg; } ;
struct sii8620 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sii8620_mt_msc_cmd_send ; 
 struct sii8620_mt_msg* sii8620_mt_msg_new (struct sii8620*) ; 

__attribute__((used)) static void sii8620_mt_msc_cmd(struct sii8620 *ctx, u8 cmd, u8 arg1, u8 arg2)
{
	struct sii8620_mt_msg *msg = sii8620_mt_msg_new(ctx);

	if (!msg)
		return;

	msg->reg[0] = cmd;
	msg->reg[1] = arg1;
	msg->reg[2] = arg2;
	msg->send = sii8620_mt_msc_cmd_send;
}