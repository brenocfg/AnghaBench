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
struct arch_hw_breakpoint {int type; int len; int /*<<< orphan*/  address; } ;
struct TYPE_4__ {int enabled; int /*<<< orphan*/  address; } ;
struct TYPE_3__ {int /*<<< orphan*/  address; } ;

/* Variables and functions */
 int HW_BRK_TYPE_DABR ; 
 int HW_BRK_TYPE_PRIV_ALL ; 
 int /*<<< orphan*/  __set_breakpoint (struct arch_hw_breakpoint*) ; 
 TYPE_2__ dabr ; 
 TYPE_1__* iabr ; 
 int /*<<< orphan*/  set_ciabr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void insert_cpu_bpts(void)
{
	struct arch_hw_breakpoint brk;

	if (dabr.enabled) {
		brk.address = dabr.address;
		brk.type = (dabr.enabled & HW_BRK_TYPE_DABR) | HW_BRK_TYPE_PRIV_ALL;
		brk.len = 8;
		__set_breakpoint(&brk);
	}

	if (iabr)
		set_ciabr(iabr->address);
}