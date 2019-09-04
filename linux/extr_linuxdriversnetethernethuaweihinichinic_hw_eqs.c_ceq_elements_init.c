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
struct hinic_eq {int q_len; } ;

/* Variables and functions */
 int /*<<< orphan*/ * GET_CEQ_ELEM (struct hinic_eq*,int) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void ceq_elements_init(struct hinic_eq *eq, u32 init_val)
{
	u32 *ceqe;
	int i;

	for (i = 0; i < eq->q_len; i++) {
		ceqe = GET_CEQ_ELEM(eq, i);
		*(ceqe) = cpu_to_be32(init_val);
	}

	wmb();  /* Write the initilzation values */
}