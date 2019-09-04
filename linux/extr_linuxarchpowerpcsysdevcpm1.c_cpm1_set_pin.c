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
typedef  enum cpm_port { ____Placeholder_cpm_port } cpm_port ;

/* Variables and functions */
 int CPM_PORTB ; 
 int CPM_PORTE ; 
 int /*<<< orphan*/  cpm1_set_pin16 (int,int,int) ; 
 int /*<<< orphan*/  cpm1_set_pin32 (int,int,int) ; 

void cpm1_set_pin(enum cpm_port port, int pin, int flags)
{
	if (port == CPM_PORTB || port == CPM_PORTE)
		cpm1_set_pin32(port, pin, flags);
	else
		cpm1_set_pin16(port, pin, flags);
}