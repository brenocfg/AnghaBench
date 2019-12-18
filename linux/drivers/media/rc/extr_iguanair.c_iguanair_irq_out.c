#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct urb {int /*<<< orphan*/  status; struct iguanair* context; } ;
struct iguanair {int /*<<< orphan*/  completion; TYPE_2__* packet; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {scalar_t__ cmd; } ;
struct TYPE_4__ {TYPE_1__ header; } ;

/* Variables and functions */
 scalar_t__ CMD_NOP ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iguanair_irq_out(struct urb *urb)
{
	struct iguanair *ir = urb->context;

	if (urb->status)
		dev_dbg(ir->dev, "Error: out urb status = %d\n", urb->status);

	/* if we sent an nop packet, do not expect a response */
	if (urb->status == 0 && ir->packet->header.cmd == CMD_NOP)
		complete(&ir->completion);
}