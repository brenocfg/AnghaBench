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
 scalar_t__ ESR_ELx_EC (unsigned int) ; 
 scalar_t__ ESR_ELx_EC_IABT_CUR ; 

__attribute__((used)) static bool is_el1_instruction_abort(unsigned int esr)
{
	return ESR_ELx_EC(esr) == ESR_ELx_EC_IABT_CUR;
}