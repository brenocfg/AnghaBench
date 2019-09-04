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
struct dm_thin_device {int dummy; } ;
struct dm_cell_key {int virtual; void* block_end; void* block_begin; int /*<<< orphan*/  dev; } ;
typedef  enum lock_space { ____Placeholder_lock_space } lock_space ;
typedef  void* dm_block_t ;

/* Variables and functions */
 int VIRTUAL ; 
 int /*<<< orphan*/  dm_thin_dev_id (struct dm_thin_device*) ; 

__attribute__((used)) static void build_key(struct dm_thin_device *td, enum lock_space ls,
		      dm_block_t b, dm_block_t e, struct dm_cell_key *key)
{
	key->virtual = (ls == VIRTUAL);
	key->dev = dm_thin_dev_id(td);
	key->block_begin = b;
	key->block_end = e;
}