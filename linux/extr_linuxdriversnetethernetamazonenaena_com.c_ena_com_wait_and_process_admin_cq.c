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
struct ena_comp_ctx {int dummy; } ;
struct ena_com_admin_queue {scalar_t__ polling; } ;

/* Variables and functions */
 int ena_com_wait_and_process_admin_cq_interrupts (struct ena_comp_ctx*,struct ena_com_admin_queue*) ; 
 int ena_com_wait_and_process_admin_cq_polling (struct ena_comp_ctx*,struct ena_com_admin_queue*) ; 

__attribute__((used)) static int ena_com_wait_and_process_admin_cq(struct ena_comp_ctx *comp_ctx,
					     struct ena_com_admin_queue *admin_queue)
{
	if (admin_queue->polling)
		return ena_com_wait_and_process_admin_cq_polling(comp_ctx,
								 admin_queue);

	return ena_com_wait_and_process_admin_cq_interrupts(comp_ctx,
							    admin_queue);
}