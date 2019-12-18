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
struct path_info {int /*<<< orphan*/  repeat_count; } ;
struct dm_path {struct path_info* pscontext; } ;
typedef  int status_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMEMIT (char*,...) ; 
#define  STATUSTYPE_INFO 129 
#define  STATUSTYPE_TABLE 128 

__attribute__((used)) static int rr_status(struct path_selector *ps, struct dm_path *path,
		     status_type_t type, char *result, unsigned int maxlen)
{
	struct path_info *pi;
	int sz = 0;

	if (!path)
		DMEMIT("0 ");
	else {
		switch(type) {
		case STATUSTYPE_INFO:
			break;
		case STATUSTYPE_TABLE:
			pi = path->pscontext;
			DMEMIT("%u ", pi->repeat_count);
			break;
		}
	}

	return sz;
}