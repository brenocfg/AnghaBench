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
struct dm_cache_metadata {int changed; } ;
typedef  int /*<<< orphan*/  dm_dblock_t ;

/* Variables and functions */
 int __clear_discard (struct dm_cache_metadata*,int /*<<< orphan*/ ) ; 
 int __set_discard (struct dm_cache_metadata*,int /*<<< orphan*/ ) ; 
 int stub1 (struct dm_cache_metadata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __discard(struct dm_cache_metadata *cmd,
		     dm_dblock_t dblock, bool discard)
{
	int r;

	r = (discard ? __set_discard : __clear_discard)(cmd, dblock);
	if (r)
		return r;

	cmd->changed = true;
	return 0;
}