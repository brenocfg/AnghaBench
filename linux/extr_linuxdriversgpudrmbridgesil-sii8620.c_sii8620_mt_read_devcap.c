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
struct sii8620_mt_msg {int /*<<< orphan*/  recv; int /*<<< orphan*/  send; int /*<<< orphan*/ * reg; } ;
struct sii8620 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MHL_READ_DEVCAP ; 
 int /*<<< orphan*/  MHL_READ_XDEVCAP ; 
 struct sii8620_mt_msg* sii8620_mt_msg_new (struct sii8620*) ; 
 int /*<<< orphan*/  sii8620_mt_read_devcap_recv ; 
 int /*<<< orphan*/  sii8620_mt_read_devcap_send ; 

__attribute__((used)) static void sii8620_mt_read_devcap(struct sii8620 *ctx, bool xdevcap)
{
	struct sii8620_mt_msg *msg = sii8620_mt_msg_new(ctx);

	if (!msg)
		return;

	msg->reg[0] = xdevcap ? MHL_READ_XDEVCAP : MHL_READ_DEVCAP;
	msg->send = sii8620_mt_read_devcap_send;
	msg->recv = sii8620_mt_read_devcap_recv;
}