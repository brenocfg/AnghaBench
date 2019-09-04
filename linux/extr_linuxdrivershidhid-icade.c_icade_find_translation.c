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
typedef  size_t u16 ;
struct icade_key {int dummy; } ;

/* Variables and functions */
 size_t ICADE_MAX_USAGE ; 
 struct icade_key const* icade_usage_table ; 

__attribute__((used)) static const struct icade_key *icade_find_translation(u16 from)
{
	if (from > ICADE_MAX_USAGE)
		return NULL;
	return &icade_usage_table[from];
}