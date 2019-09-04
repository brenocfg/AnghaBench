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
typedef  int /*<<< orphan*/  u32 ;
struct hinic_eq {int q_len; int wrapped; int cons_idx; } ;
struct hinic_ceqs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * GET_CURR_CEQ_ELEM (struct hinic_eq*) ; 
 int HINIC_EQ_ELEM_DESC_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRAPPED ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceq_event_handler (struct hinic_ceqs*,int /*<<< orphan*/ ) ; 
 struct hinic_ceqs* ceq_to_ceqs (struct hinic_eq*) ; 

__attribute__((used)) static void ceq_irq_handler(struct hinic_eq *eq)
{
	struct hinic_ceqs *ceqs = ceq_to_ceqs(eq);
	u32 ceqe;
	int i;

	for (i = 0; i < eq->q_len; i++) {
		ceqe = *(GET_CURR_CEQ_ELEM(eq));

		/* Data in HW is in Big endian Format */
		ceqe = be32_to_cpu(ceqe);

		/* HW toggles the wrapped bit, when it adds eq element event */
		if (HINIC_EQ_ELEM_DESC_GET(ceqe, WRAPPED) == eq->wrapped)
			break;

		ceq_event_handler(ceqs, ceqe);

		eq->cons_idx++;

		if (eq->cons_idx == eq->q_len) {
			eq->cons_idx = 0;
			eq->wrapped = !eq->wrapped;
		}
	}
}