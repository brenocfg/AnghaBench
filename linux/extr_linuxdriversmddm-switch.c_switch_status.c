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
struct switch_ctx {int nr_paths; unsigned long long region_size; TYPE_2__* path_list; } ;
struct dm_target {struct switch_ctx* private; } ;
typedef  int status_type_t ;
struct TYPE_4__ {scalar_t__ start; TYPE_1__* dmdev; } ;
struct TYPE_3__ {int name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMEMIT (char*,int,unsigned long long) ; 
#define  STATUSTYPE_INFO 129 
#define  STATUSTYPE_TABLE 128 

__attribute__((used)) static void switch_status(struct dm_target *ti, status_type_t type,
			  unsigned status_flags, char *result, unsigned maxlen)
{
	struct switch_ctx *sctx = ti->private;
	unsigned sz = 0;
	int path_nr;

	switch (type) {
	case STATUSTYPE_INFO:
		result[0] = '\0';
		break;

	case STATUSTYPE_TABLE:
		DMEMIT("%u %u 0", sctx->nr_paths, sctx->region_size);
		for (path_nr = 0; path_nr < sctx->nr_paths; path_nr++)
			DMEMIT(" %s %llu", sctx->path_list[path_nr].dmdev->name,
			       (unsigned long long)sctx->path_list[path_nr].start);
		break;
	}
}