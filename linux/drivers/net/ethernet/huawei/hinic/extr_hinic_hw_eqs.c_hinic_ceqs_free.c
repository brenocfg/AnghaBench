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
struct hinic_ceqs {int num_ceqs; int /*<<< orphan*/ * ceq; } ;

/* Variables and functions */
 int /*<<< orphan*/  remove_eq (int /*<<< orphan*/ *) ; 

void hinic_ceqs_free(struct hinic_ceqs *ceqs)
{
	int q_id;

	for (q_id = 0; q_id < ceqs->num_ceqs; q_id++)
		remove_eq(&ceqs->ceq[q_id]);
}