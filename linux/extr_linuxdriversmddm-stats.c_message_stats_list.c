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
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dm_get_stats (struct mapped_device*) ; 
 int dm_stats_list (int /*<<< orphan*/ ,char const*,char*,unsigned int) ; 
 int /*<<< orphan*/  kfree (char const*) ; 
 char* kstrdup (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int message_stats_list(struct mapped_device *md,
			      unsigned argc, char **argv,
			      char *result, unsigned maxlen)
{
	int r;
	const char *program = NULL;

	if (argc < 1 || argc > 2)
		return -EINVAL;

	if (argc > 1) {
		program = kstrdup(argv[1], GFP_KERNEL);
		if (!program)
			return -ENOMEM;
	}

	r = dm_stats_list(dm_get_stats(md), program, result, maxlen);

	kfree(program);

	return r;
}