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
struct ps2dev {int flags; int nak; int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 int PS2_FLAG_ACK ; 
 int PS2_FLAG_CMD ; 
 int PS2_FLAG_NAK ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void ps2_cmd_aborted(struct ps2dev *ps2dev)
{
	if (ps2dev->flags & PS2_FLAG_ACK)
		ps2dev->nak = 1;

	if (ps2dev->flags & (PS2_FLAG_ACK | PS2_FLAG_CMD))
		wake_up(&ps2dev->wait);

	/* reset all flags except last nack */
	ps2dev->flags &= PS2_FLAG_NAK;
}