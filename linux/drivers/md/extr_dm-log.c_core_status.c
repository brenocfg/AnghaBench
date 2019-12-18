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
struct log_c {int /*<<< orphan*/  region_size; int /*<<< orphan*/  sync; } ;
struct dm_dirty_log {TYPE_1__* type; struct log_c* context; } ;
typedef  int status_type_t ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULTSYNC ; 
 int /*<<< orphan*/  DMEMIT (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  DMEMIT_SYNC ; 
#define  STATUSTYPE_INFO 129 
#define  STATUSTYPE_TABLE 128 

__attribute__((used)) static int core_status(struct dm_dirty_log *log, status_type_t status,
		       char *result, unsigned int maxlen)
{
	int sz = 0;
	struct log_c *lc = log->context;

	switch(status) {
	case STATUSTYPE_INFO:
		DMEMIT("1 %s", log->type->name);
		break;

	case STATUSTYPE_TABLE:
		DMEMIT("%s %u %u ", log->type->name,
		       lc->sync == DEFAULTSYNC ? 1 : 2, lc->region_size);
		DMEMIT_SYNC;
	}

	return sz;
}