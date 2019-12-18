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
struct log_c {int /*<<< orphan*/  region_size; TYPE_2__* log_dev; int /*<<< orphan*/  sync; int /*<<< orphan*/  log_dev_failed; int /*<<< orphan*/  log_dev_flush_failed; } ;
struct dm_dirty_log {TYPE_1__* type; struct log_c* context; } ;
typedef  int status_type_t ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULTSYNC ; 
 int /*<<< orphan*/  DMEMIT (char*,int /*<<< orphan*/ ,int,float,...) ; 
 int /*<<< orphan*/  DMEMIT_SYNC ; 
#define  STATUSTYPE_INFO 129 
#define  STATUSTYPE_TABLE 128 

__attribute__((used)) static int disk_status(struct dm_dirty_log *log, status_type_t status,
		       char *result, unsigned int maxlen)
{
	int sz = 0;
	struct log_c *lc = log->context;

	switch(status) {
	case STATUSTYPE_INFO:
		DMEMIT("3 %s %s %c", log->type->name, lc->log_dev->name,
		       lc->log_dev_flush_failed ? 'F' :
		       lc->log_dev_failed ? 'D' :
		       'A');
		break;

	case STATUSTYPE_TABLE:
		DMEMIT("%s %u %s %u ", log->type->name,
		       lc->sync == DEFAULTSYNC ? 2 : 3, lc->log_dev->name,
		       lc->region_size);
		DMEMIT_SYNC;
	}

	return sz;
}