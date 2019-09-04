#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int raid_disks; } ;
struct r10conf {int have_replacement; scalar_t__ next_resync; int /*<<< orphan*/  r10buf_pool; TYPE_2__* mirrors; TYPE_1__ geo; } ;
struct TYPE_4__ {scalar_t__ replacement; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int RESYNC_BLOCK_SIZE ; 
 int RESYNC_WINDOW ; 
 int mempool_init (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct r10conf*) ; 
 int /*<<< orphan*/  mempool_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r10buf_pool_alloc ; 
 int /*<<< orphan*/  r10buf_pool_free ; 

__attribute__((used)) static int init_resync(struct r10conf *conf)
{
	int ret, buffs, i;

	buffs = RESYNC_WINDOW / RESYNC_BLOCK_SIZE;
	BUG_ON(mempool_initialized(&conf->r10buf_pool));
	conf->have_replacement = 0;
	for (i = 0; i < conf->geo.raid_disks; i++)
		if (conf->mirrors[i].replacement)
			conf->have_replacement = 1;
	ret = mempool_init(&conf->r10buf_pool, buffs,
			   r10buf_pool_alloc, r10buf_pool_free, conf);
	if (ret)
		return ret;
	conf->next_resync = 0;
	return 0;
}