#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int entries; int step; int first; int next; int last; } ;
struct TYPE_4__ {int entries; int step; int first; int next; int last; } ;
struct TYPE_6__ {TYPE_2__ itlb; TYPE_1__ dtlb; } ;

/* Variables and functions */
 int DTLB_FIXED ; 
 int ITLB_FIXED ; 
 TYPE_3__* cpu_data ; 

int sh64_tlb_init(void)
{
	/* Assign some sane DTLB defaults */
	cpu_data->dtlb.entries	= 64;
	cpu_data->dtlb.step	= 0x10;

	cpu_data->dtlb.first	= DTLB_FIXED | cpu_data->dtlb.step;
	cpu_data->dtlb.next	= cpu_data->dtlb.first;

	cpu_data->dtlb.last	= DTLB_FIXED |
				  ((cpu_data->dtlb.entries - 1) *
				   cpu_data->dtlb.step);

	/* And again for the ITLB */
	cpu_data->itlb.entries	= 64;
	cpu_data->itlb.step	= 0x10;

	cpu_data->itlb.first	= ITLB_FIXED | cpu_data->itlb.step;
	cpu_data->itlb.next	= cpu_data->itlb.first;
	cpu_data->itlb.last	= ITLB_FIXED |
				  ((cpu_data->itlb.entries - 1) *
				   cpu_data->itlb.step);

	return 0;
}