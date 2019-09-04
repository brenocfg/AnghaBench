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
struct vnic_rq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  vnic_rq_init_start (struct vnic_rq*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

void vnic_rq_init(struct vnic_rq *rq, unsigned int cq_index,
	unsigned int error_interrupt_enable,
	unsigned int error_interrupt_offset)
{
	vnic_rq_init_start(rq, cq_index, 0, 0, error_interrupt_enable,
			   error_interrupt_offset);
}