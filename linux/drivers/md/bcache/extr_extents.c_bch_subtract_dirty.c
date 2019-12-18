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
typedef  int /*<<< orphan*/  uint64_t ;
struct cache_set {int dummy; } ;
struct bkey {int dummy; } ;

/* Variables and functions */
 scalar_t__ KEY_DIRTY (struct bkey*) ; 
 int /*<<< orphan*/  KEY_INODE (struct bkey*) ; 
 int /*<<< orphan*/  bcache_dev_sectors_dirty_add (struct cache_set*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void bch_subtract_dirty(struct bkey *k,
			   struct cache_set *c,
			   uint64_t offset,
			   int sectors)
{
	if (KEY_DIRTY(k))
		bcache_dev_sectors_dirty_add(c, KEY_INODE(k),
					     offset, -sectors);
}