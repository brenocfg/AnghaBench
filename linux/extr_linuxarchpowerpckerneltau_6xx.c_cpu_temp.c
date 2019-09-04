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
typedef  int u32 ;
struct TYPE_2__ {int high; int low; } ;

/* Variables and functions */
 TYPE_1__* tau ; 

u32 cpu_temp(unsigned long cpu)
{
	return ((tau[cpu].high + tau[cpu].low) / 2);
}