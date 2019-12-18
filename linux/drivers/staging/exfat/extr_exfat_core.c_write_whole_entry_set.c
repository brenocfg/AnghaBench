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
struct super_block {int dummy; } ;
struct entry_set_cache_t {int /*<<< orphan*/  num_entries; int /*<<< orphan*/  offset; int /*<<< orphan*/  sector; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  __write_partial_entries_in_entry_set (struct super_block*,struct entry_set_cache_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

s32 write_whole_entry_set(struct super_block *sb, struct entry_set_cache_t *es)
{
	return __write_partial_entries_in_entry_set(sb, es, es->sector,
						    es->offset,
						    es->num_entries);
}