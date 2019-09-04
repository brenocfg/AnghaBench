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
struct ib_smp {int dummy; } ;
struct ib_device {int dummy; } ;
struct ib_cc_mad {scalar_t__ mgmt_data; } ;
struct ib_cc_classportinfo_attr {int base_version; int class_version; int resp_time_value; scalar_t__ cap_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int reply (struct ib_smp*) ; 

__attribute__((used)) static int cc_get_classportinfo(struct ib_cc_mad *ccp,
				struct ib_device *ibdev)
{
	struct ib_cc_classportinfo_attr *p =
		(struct ib_cc_classportinfo_attr *)ccp->mgmt_data;

	memset(ccp->mgmt_data, 0, sizeof(ccp->mgmt_data));

	p->base_version = 1;
	p->class_version = 1;
	p->cap_mask = 0;

	/*
	 * Expected response time is 4.096 usec. * 2^18 == 1.073741824 sec.
	 */
	p->resp_time_value = 18;

	return reply((struct ib_smp *) ccp);
}