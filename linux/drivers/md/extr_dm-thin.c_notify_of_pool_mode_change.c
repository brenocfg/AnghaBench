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
struct TYPE_3__ {int /*<<< orphan*/  error_if_no_space; } ;
struct pool {int /*<<< orphan*/  pool_md; TYPE_2__* ti; TYPE_1__ pf; } ;
typedef  enum pool_mode { ____Placeholder_pool_mode } pool_mode ;
struct TYPE_4__ {int /*<<< orphan*/  table; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMINFO (char*,int /*<<< orphan*/ ,char const*,char*) ; 
 int PM_OUT_OF_DATA_SPACE ; 
 int /*<<< orphan*/  dm_device_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_table_event (int /*<<< orphan*/ ) ; 
 int get_pool_mode (struct pool*) ; 

__attribute__((used)) static void notify_of_pool_mode_change(struct pool *pool)
{
	const char *descs[] = {
		"write",
		"out-of-data-space",
		"read-only",
		"read-only",
		"fail"
	};
	const char *extra_desc = NULL;
	enum pool_mode mode = get_pool_mode(pool);

	if (mode == PM_OUT_OF_DATA_SPACE) {
		if (!pool->pf.error_if_no_space)
			extra_desc = " (queue IO)";
		else
			extra_desc = " (error IO)";
	}

	dm_table_event(pool->ti->table);
	DMINFO("%s: switching pool to %s%s mode",
	       dm_device_name(pool->pool_md),
	       descs[(int)mode], extra_desc ? : "");
}