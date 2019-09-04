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
struct pool {int /*<<< orphan*/  pmd; } ;
typedef  int /*<<< orphan*/  dm_thin_id ;

/* Variables and functions */
 int /*<<< orphan*/  DMWARN (char*,char*) ; 
 int check_arg_count (unsigned int,int) ; 
 int dm_pool_create_thin (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int read_dev_id (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int process_create_thin_mesg(unsigned argc, char **argv, struct pool *pool)
{
	dm_thin_id dev_id;
	int r;

	r = check_arg_count(argc, 2);
	if (r)
		return r;

	r = read_dev_id(argv[1], &dev_id, 1);
	if (r)
		return r;

	r = dm_pool_create_thin(pool->pmd, dev_id);
	if (r) {
		DMWARN("Creation of new thinly-provisioned device with id %s failed.",
		       argv[1]);
		return r;
	}

	return 0;
}