#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ step; int /*<<< orphan*/  next; int /*<<< orphan*/  first; } ;
struct TYPE_4__ {TYPE_1__ dtlb; } ;

/* Variables and functions */
 TYPE_2__* cpu_data ; 
 unsigned long long sh64_next_free_dtlb_entry () ; 

unsigned long long sh64_get_wired_dtlb_entry(void)
{
	unsigned long long entry = sh64_next_free_dtlb_entry();

	cpu_data->dtlb.first += cpu_data->dtlb.step;
	cpu_data->dtlb.next  += cpu_data->dtlb.step;

	return entry;
}