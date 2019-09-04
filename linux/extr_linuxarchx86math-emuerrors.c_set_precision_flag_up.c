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

/* Variables and functions */
 int CW_Precision ; 
 int /*<<< orphan*/  EXCEPTION (int) ; 
 int EX_Precision ; 
 int SW_C1 ; 
 int SW_Precision ; 
 int control_word ; 
 int partial_status ; 

void set_precision_flag_up(void)
{
	if (control_word & CW_Precision)
		partial_status |= (SW_Precision | SW_C1);	/* The masked response */
	else
		EXCEPTION(EX_Precision | SW_C1);
}