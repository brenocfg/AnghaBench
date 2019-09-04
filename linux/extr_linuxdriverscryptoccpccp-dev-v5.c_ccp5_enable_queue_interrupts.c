#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ccp_device {unsigned int cmd_q_count; TYPE_1__* cmd_q; } ;
struct TYPE_2__ {int /*<<< orphan*/  reg_int_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  SUPPORTED_INTERRUPTS ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ccp5_enable_queue_interrupts(struct ccp_device *ccp)
{
	unsigned int i;

	for (i = 0; i < ccp->cmd_q_count; i++)
		iowrite32(SUPPORTED_INTERRUPTS, ccp->cmd_q[i].reg_int_enable);
}