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
struct dm_writecache {int dummy; } ;
struct dm_target {struct dm_writecache* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*,char*) ; 
 int EINVAL ; 
 int process_flush_mesg (unsigned int,char**,struct dm_writecache*) ; 
 int process_flush_on_suspend_mesg (unsigned int,char**,struct dm_writecache*) ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 

__attribute__((used)) static int writecache_message(struct dm_target *ti, unsigned argc, char **argv,
			      char *result, unsigned maxlen)
{
	int r = -EINVAL;
	struct dm_writecache *wc = ti->private;

	if (!strcasecmp(argv[0], "flush"))
		r = process_flush_mesg(argc, argv, wc);
	else if (!strcasecmp(argv[0], "flush_on_suspend"))
		r = process_flush_on_suspend_mesg(argc, argv, wc);
	else
		DMERR("unrecognised message received: %s", argv[0]);

	return r;
}