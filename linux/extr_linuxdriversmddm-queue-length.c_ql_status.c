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
struct path_selector {int dummy; } ;
struct path_info {int /*<<< orphan*/  repeat_count; int /*<<< orphan*/  qlen; } ;
struct dm_path {struct path_info* pscontext; } ;
typedef  int status_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMEMIT (char*,...) ; 
#define  STATUSTYPE_INFO 129 
#define  STATUSTYPE_TABLE 128 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ql_status(struct path_selector *ps, struct dm_path *path,
		     status_type_t type, char *result, unsigned maxlen)
{
	unsigned sz = 0;
	struct path_info *pi;

	/* When called with NULL path, return selector status/args. */
	if (!path)
		DMEMIT("0 ");
	else {
		pi = path->pscontext;

		switch (type) {
		case STATUSTYPE_INFO:
			DMEMIT("%d ", atomic_read(&pi->qlen));
			break;
		case STATUSTYPE_TABLE:
			DMEMIT("%u ", pi->repeat_count);
			break;
		}
	}

	return sz;
}