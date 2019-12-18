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
struct iguanair {int /*<<< orphan*/  rc; TYPE_2__* packet; } ;
struct TYPE_3__ {int /*<<< orphan*/  cmd; int /*<<< orphan*/  direction; scalar_t__ start; } ;
struct TYPE_4__ {TYPE_1__ header; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_RECEIVER_OFF ; 
 int /*<<< orphan*/  CMD_RECEIVER_ON ; 
 int /*<<< orphan*/  DIR_OUT ; 
 int iguanair_send (struct iguanair*,int) ; 
 int /*<<< orphan*/  ir_raw_event_reset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iguanair_receiver(struct iguanair *ir, bool enable)
{
	ir->packet->header.start = 0;
	ir->packet->header.direction = DIR_OUT;
	ir->packet->header.cmd = enable ? CMD_RECEIVER_ON : CMD_RECEIVER_OFF;

	if (enable)
		ir_raw_event_reset(ir->rc);

	return iguanair_send(ir, sizeof(ir->packet->header));
}