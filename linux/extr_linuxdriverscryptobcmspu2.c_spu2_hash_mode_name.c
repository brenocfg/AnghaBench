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
typedef  enum spu2_hash_mode { ____Placeholder_spu2_hash_mode } spu2_hash_mode ;

/* Variables and functions */
 int SPU2_HASH_MODE_LAST ; 
 char** spu2_hash_mode_names ; 

__attribute__((used)) static char *spu2_hash_mode_name(enum spu2_hash_mode hash_mode)
{
	if (hash_mode >= SPU2_HASH_MODE_LAST)
		return "Reserved";
	return spu2_hash_mode_names[hash_mode];
}