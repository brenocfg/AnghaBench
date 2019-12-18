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
 int /*<<< orphan*/  DMWARN (char*,char*) ; 
 int EINVAL ; 
 int message_stats_clear (struct mapped_device*,unsigned int,char**) ; 
 int message_stats_create (struct mapped_device*,unsigned int,char**,char*,unsigned int) ; 
 int message_stats_delete (struct mapped_device*,unsigned int,char**) ; 
 int message_stats_list (struct mapped_device*,unsigned int,char**,char*,unsigned int) ; 
 int message_stats_print (struct mapped_device*,unsigned int,char**,int,char*,unsigned int) ; 
 int message_stats_set_aux (struct mapped_device*,unsigned int,char**) ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 

int dm_stats_message(struct mapped_device *md, unsigned argc, char **argv,
		     char *result, unsigned maxlen)
{
	int r;

	/* All messages here must start with '@' */
	if (!strcasecmp(argv[0], "@stats_create"))
		r = message_stats_create(md, argc, argv, result, maxlen);
	else if (!strcasecmp(argv[0], "@stats_delete"))
		r = message_stats_delete(md, argc, argv);
	else if (!strcasecmp(argv[0], "@stats_clear"))
		r = message_stats_clear(md, argc, argv);
	else if (!strcasecmp(argv[0], "@stats_list"))
		r = message_stats_list(md, argc, argv, result, maxlen);
	else if (!strcasecmp(argv[0], "@stats_print"))
		r = message_stats_print(md, argc, argv, false, result, maxlen);
	else if (!strcasecmp(argv[0], "@stats_print_clear"))
		r = message_stats_print(md, argc, argv, true, result, maxlen);
	else if (!strcasecmp(argv[0], "@stats_set_aux"))
		r = message_stats_set_aux(md, argc, argv);
	else
		return 2; /* this wasn't a stats message */

	if (r == -EINVAL)
		DMWARN("Invalid parameters for message %s", argv[0]);

	return r;
}