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
struct log_c {int /*<<< orphan*/  integrated_flush; int /*<<< orphan*/  uuid; int /*<<< orphan*/  usr_argc; int /*<<< orphan*/  usr_argv_str; } ;
struct dm_dirty_log {TYPE_1__* type; struct log_c* context; } ;
typedef  int status_type_t ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DMEMIT (char*,...) ; 
 int /*<<< orphan*/  DM_ULOG_STATUS_INFO ; 
#define  STATUSTYPE_INFO 129 
#define  STATUSTYPE_TABLE 128 
 char* strchr (int /*<<< orphan*/ ,char) ; 
 int userspace_do_request (struct log_c*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,size_t*) ; 

__attribute__((used)) static int userspace_status(struct dm_dirty_log *log, status_type_t status_type,
			    char *result, unsigned maxlen)
{
	int r = 0;
	char *table_args;
	size_t sz = (size_t)maxlen;
	struct log_c *lc = log->context;

	switch (status_type) {
	case STATUSTYPE_INFO:
		r = userspace_do_request(lc, lc->uuid, DM_ULOG_STATUS_INFO,
					 NULL, 0, result, &sz);

		if (r) {
			sz = 0;
			DMEMIT("%s 1 COM_FAILURE", log->type->name);
		}
		break;
	case STATUSTYPE_TABLE:
		sz = 0;
		table_args = strchr(lc->usr_argv_str, ' ');
		BUG_ON(!table_args); /* There will always be a ' ' */
		table_args++;

		DMEMIT("%s %u %s ", log->type->name, lc->usr_argc, lc->uuid);
		if (lc->integrated_flush)
			DMEMIT("integrated_flush ");
		DMEMIT("%s ", table_args);
		break;
	}
	return (r) ? 0 : (int)sz;
}