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
struct sunkbd {int reset; int type; int layout; int /*<<< orphan*/  wait; int /*<<< orphan*/  serio; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  SUNKBD_CMD_LAYOUT ; 
 int /*<<< orphan*/  SUNKBD_CMD_RESET ; 
 int SUNKBD_LAYOUT_5_MASK ; 
 int /*<<< orphan*/  serio_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int sunkbd_initialize(struct sunkbd *sunkbd)
{
	sunkbd->reset = -2;
	serio_write(sunkbd->serio, SUNKBD_CMD_RESET);
	wait_event_interruptible_timeout(sunkbd->wait, sunkbd->reset >= 0, HZ);
	if (sunkbd->reset < 0)
		return -1;

	sunkbd->type = sunkbd->reset;

	if (sunkbd->type == 4) {	/* Type 4 keyboard */
		sunkbd->layout = -2;
		serio_write(sunkbd->serio, SUNKBD_CMD_LAYOUT);
		wait_event_interruptible_timeout(sunkbd->wait,
						 sunkbd->layout >= 0, HZ / 4);
		if (sunkbd->layout < 0)
			return -1;
		if (sunkbd->layout & SUNKBD_LAYOUT_5_MASK)
			sunkbd->type = 5;
	}

	return 0;
}