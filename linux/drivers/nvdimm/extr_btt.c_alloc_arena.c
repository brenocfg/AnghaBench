#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct btt {int lbasize; TYPE_1__* nd_btt; int /*<<< orphan*/  sector_size; } ;
struct arena_info {size_t size; size_t external_lba_start; int external_lbasize; int nfree; int internal_nlba; int external_nlba; size_t infooff; int dataoff; int mapoff; int logoff; int info2off; int* log_index; void* internal_lbasize; int /*<<< orphan*/  version_minor; int /*<<< orphan*/  version_major; int /*<<< orphan*/  err_lock; int /*<<< orphan*/  sector_size; TYPE_1__* nd_btt; } ;
struct TYPE_2__ {int /*<<< orphan*/  version_minor; int /*<<< orphan*/  version_major; } ;

/* Variables and functions */
 int BTT_DEFAULT_NFREE ; 
 int BTT_PG_SIZE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int INT_LBASIZE_ALIGNMENT ; 
 int LOG_GRP_SIZE ; 
 int MAP_ENT_SIZE ; 
 int div_u64 (int,void*) ; 
 struct arena_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 void* roundup (int,int) ; 

__attribute__((used)) static struct arena_info *alloc_arena(struct btt *btt, size_t size,
				size_t start, size_t arena_off)
{
	struct arena_info *arena;
	u64 logsize, mapsize, datasize;
	u64 available = size;

	arena = kzalloc(sizeof(struct arena_info), GFP_KERNEL);
	if (!arena)
		return NULL;
	arena->nd_btt = btt->nd_btt;
	arena->sector_size = btt->sector_size;
	mutex_init(&arena->err_lock);

	if (!size)
		return arena;

	arena->size = size;
	arena->external_lba_start = start;
	arena->external_lbasize = btt->lbasize;
	arena->internal_lbasize = roundup(arena->external_lbasize,
					INT_LBASIZE_ALIGNMENT);
	arena->nfree = BTT_DEFAULT_NFREE;
	arena->version_major = btt->nd_btt->version_major;
	arena->version_minor = btt->nd_btt->version_minor;

	if (available % BTT_PG_SIZE)
		available -= (available % BTT_PG_SIZE);

	/* Two pages are reserved for the super block and its copy */
	available -= 2 * BTT_PG_SIZE;

	/* The log takes a fixed amount of space based on nfree */
	logsize = roundup(arena->nfree * LOG_GRP_SIZE, BTT_PG_SIZE);
	available -= logsize;

	/* Calculate optimal split between map and data area */
	arena->internal_nlba = div_u64(available - BTT_PG_SIZE,
			arena->internal_lbasize + MAP_ENT_SIZE);
	arena->external_nlba = arena->internal_nlba - arena->nfree;

	mapsize = roundup((arena->external_nlba * MAP_ENT_SIZE), BTT_PG_SIZE);
	datasize = available - mapsize;

	/* 'Absolute' values, relative to start of storage space */
	arena->infooff = arena_off;
	arena->dataoff = arena->infooff + BTT_PG_SIZE;
	arena->mapoff = arena->dataoff + datasize;
	arena->logoff = arena->mapoff + mapsize;
	arena->info2off = arena->logoff + logsize;

	/* Default log indices are (0,1) */
	arena->log_index[0] = 0;
	arena->log_index[1] = 1;
	return arena;
}