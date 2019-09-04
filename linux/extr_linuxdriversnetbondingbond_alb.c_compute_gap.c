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
struct slave {int speed; } ;
typedef  long long s64 ;
struct TYPE_2__ {int load; } ;

/* Variables and functions */
 TYPE_1__ SLAVE_TLB_INFO (struct slave*) ; 

__attribute__((used)) static long long compute_gap(struct slave *slave)
{
	return (s64) (slave->speed << 20) - /* Convert to Megabit per sec */
	       (s64) (SLAVE_TLB_INFO(slave).load << 3); /* Bytes to bits */
}