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
struct pool {TYPE_1__* ti; int /*<<< orphan*/  pool_md; } ;
struct TYPE_2__ {int /*<<< orphan*/  table; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMWARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_device_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_table_event (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void metadata_low_callback(void *context)
{
	struct pool *pool = context;

	DMWARN("%s: reached low water mark for metadata device: sending event.",
	       dm_device_name(pool->pool_md));

	dm_table_event(pool->ti->table);
}