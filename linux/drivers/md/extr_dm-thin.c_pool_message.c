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
struct pool_c {struct pool* pool; } ;
struct pool {int /*<<< orphan*/  pool_md; } ;
struct dm_target {struct pool_c* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMWARN (char*,char*) ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 scalar_t__ PM_OUT_OF_METADATA_SPACE ; 
 int /*<<< orphan*/  commit (struct pool*) ; 
 int /*<<< orphan*/  dm_device_name (int /*<<< orphan*/ ) ; 
 scalar_t__ get_pool_mode (struct pool*) ; 
 int process_create_snap_mesg (unsigned int,char**,struct pool*) ; 
 int process_create_thin_mesg (unsigned int,char**,struct pool*) ; 
 int process_delete_mesg (unsigned int,char**,struct pool*) ; 
 int process_release_metadata_snap_mesg (unsigned int,char**,struct pool*) ; 
 int process_reserve_metadata_snap_mesg (unsigned int,char**,struct pool*) ; 
 int process_set_transaction_id_mesg (unsigned int,char**,struct pool*) ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 

__attribute__((used)) static int pool_message(struct dm_target *ti, unsigned argc, char **argv,
			char *result, unsigned maxlen)
{
	int r = -EINVAL;
	struct pool_c *pt = ti->private;
	struct pool *pool = pt->pool;

	if (get_pool_mode(pool) >= PM_OUT_OF_METADATA_SPACE) {
		DMERR("%s: unable to service pool target messages in READ_ONLY or FAIL mode",
		      dm_device_name(pool->pool_md));
		return -EOPNOTSUPP;
	}

	if (!strcasecmp(argv[0], "create_thin"))
		r = process_create_thin_mesg(argc, argv, pool);

	else if (!strcasecmp(argv[0], "create_snap"))
		r = process_create_snap_mesg(argc, argv, pool);

	else if (!strcasecmp(argv[0], "delete"))
		r = process_delete_mesg(argc, argv, pool);

	else if (!strcasecmp(argv[0], "set_transaction_id"))
		r = process_set_transaction_id_mesg(argc, argv, pool);

	else if (!strcasecmp(argv[0], "reserve_metadata_snap"))
		r = process_reserve_metadata_snap_mesg(argc, argv, pool);

	else if (!strcasecmp(argv[0], "release_metadata_snap"))
		r = process_release_metadata_snap_mesg(argc, argv, pool);

	else
		DMWARN("Unrecognised thin pool target message received: %s", argv[0]);

	if (!r)
		(void) commit(pool);

	return r;
}