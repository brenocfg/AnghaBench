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
struct mapped_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*,...) ; 
 int EINVAL ; 
 int dm_cancel_deferred_remove (struct mapped_device*) ; 
 int dm_stats_message (struct mapped_device*,unsigned int,char**,char*,unsigned int) ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 

__attribute__((used)) static int message_for_md(struct mapped_device *md, unsigned argc, char **argv,
			  char *result, unsigned maxlen)
{
	int r;

	if (**argv != '@')
		return 2; /* no '@' prefix, deliver to target */

	if (!strcasecmp(argv[0], "@cancel_deferred_remove")) {
		if (argc != 1) {
			DMERR("Invalid arguments for @cancel_deferred_remove");
			return -EINVAL;
		}
		return dm_cancel_deferred_remove(md);
	}

	r = dm_stats_message(md, argc, argv, result, maxlen);
	if (r < 2)
		return r;

	DMERR("Unsupported message sent to DM core: %s", argv[0]);
	return -EINVAL;
}