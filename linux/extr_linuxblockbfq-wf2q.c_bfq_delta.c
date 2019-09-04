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
typedef  int u64 ;

/* Variables and functions */
 int WFQ_SERVICE_SHIFT ; 
 int /*<<< orphan*/  do_div (int,unsigned long) ; 

__attribute__((used)) static u64 bfq_delta(unsigned long service, unsigned long weight)
{
	u64 d = (u64)service << WFQ_SERVICE_SHIFT;

	do_div(d, weight);
	return d;
}