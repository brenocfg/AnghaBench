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
typedef  int u64 ;
struct arena_info {int dataoff; int internal_lbasize; } ;

/* Variables and functions */

__attribute__((used)) static u64 to_namespace_offset(struct arena_info *arena, u64 lba)
{
	return arena->dataoff + ((u64)lba * arena->internal_lbasize);
}