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

__attribute__((used)) static u32 sh_msiof_get_delay_bit(u32 dtdl_or_syncdl)
{
	/*
	 * DTDL/SYNCDL bit	: p->info->dtdl or p->info->syncdl
	 * b'000		: 0
	 * b'001		: 100
	 * b'010		: 200
	 * b'011 (SYNCDL only)	: 300
	 * b'101		: 50
	 * b'110		: 150
	 */
	if (dtdl_or_syncdl % 100)
		return dtdl_or_syncdl / 100 + 5;
	else
		return dtdl_or_syncdl / 100;
}