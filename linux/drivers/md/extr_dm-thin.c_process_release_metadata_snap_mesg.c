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

/* Variables and functions */
 int /*<<< orphan*/  DMWARN (char*) ; 
 int check_arg_count (unsigned int,int) ; 
 int dm_pool_release_metadata_snap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int process_release_metadata_snap_mesg(unsigned argc, char **argv, struct pool *pool)
{
	int r;

	r = check_arg_count(argc, 1);
	if (r)
		return r;

	r = dm_pool_release_metadata_snap(pool->pmd);
	if (r)
		DMWARN("release_metadata_snap message failed.");

	return r;
}