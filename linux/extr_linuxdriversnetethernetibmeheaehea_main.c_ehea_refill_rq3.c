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
struct ehea_port_res {int /*<<< orphan*/  rq3_skba; } ;

/* Variables and functions */
 int /*<<< orphan*/  EHEA_MAX_PACKET_SIZE ; 
 int /*<<< orphan*/  EHEA_RWQE3_TYPE ; 
 int ehea_refill_rq_def (struct ehea_port_res*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ehea_refill_rq3(struct ehea_port_res *pr, int nr_of_wqes)
{
	return ehea_refill_rq_def(pr, &pr->rq3_skba, 3,
				  nr_of_wqes, EHEA_RWQE3_TYPE,
				  EHEA_MAX_PACKET_SIZE);
}