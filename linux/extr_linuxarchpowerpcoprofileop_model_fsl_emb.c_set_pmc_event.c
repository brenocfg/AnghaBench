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
typedef  int u32 ;

/* Variables and functions */
 int PMLCA_EVENT_MASK ; 
 int PMLCA_EVENT_SHIFT ; 
 int get_pmlca (int) ; 
 int /*<<< orphan*/  set_pmlca (int,int) ; 

__attribute__((used)) static void set_pmc_event(int ctr, int event)
{
	u32 pmlca;

	pmlca = get_pmlca(ctr);

	pmlca = (pmlca & ~PMLCA_EVENT_MASK) |
		((event << PMLCA_EVENT_SHIFT) &
		 PMLCA_EVENT_MASK);

	set_pmlca(ctr, pmlca);
}