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
struct ena_com_dev {int /*<<< orphan*/  admin_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  ena_com_handle_admin_completion (int /*<<< orphan*/ *) ; 

void ena_com_admin_q_comp_intr_handler(struct ena_com_dev *ena_dev)
{
	ena_com_handle_admin_completion(&ena_dev->admin_queue);
}