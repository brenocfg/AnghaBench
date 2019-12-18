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
struct TYPE_3__ {int /*<<< orphan*/  send_fifobar; } ;
struct ccb {TYPE_1__ ccb_u1; } ;
struct TYPE_4__ {int reset; } ;

/* Variables and functions */
 TYPE_2__* FIFOBARTOHANDLE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void set_channel_reset(struct ccb *ccb)
{
	/* set a flag indicating this channel needs a reset */
	FIFOBARTOHANDLE(ccb->ccb_u1.send_fifobar)->reset = 1;
}