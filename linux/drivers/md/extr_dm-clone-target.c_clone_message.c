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
struct dm_target {struct clone* private; } ;
struct clone {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*,int /*<<< orphan*/ ,char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  clone_device_name (struct clone*) ; 
 int /*<<< orphan*/  disable_hydration (struct clone*) ; 
 int /*<<< orphan*/  enable_hydration (struct clone*) ; 
 scalar_t__ kstrtouint (char*,int,unsigned int*) ; 
 int /*<<< orphan*/  set_hydration_batch_size (struct clone*,unsigned int) ; 
 int /*<<< orphan*/  set_hydration_threshold (struct clone*,unsigned int) ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 

__attribute__((used)) static int clone_message(struct dm_target *ti, unsigned int argc, char **argv,
			 char *result, unsigned int maxlen)
{
	struct clone *clone = ti->private;
	unsigned int value;

	if (!argc)
		return -EINVAL;

	if (!strcasecmp(argv[0], "enable_hydration")) {
		enable_hydration(clone);
		return 0;
	}

	if (!strcasecmp(argv[0], "disable_hydration")) {
		disable_hydration(clone);
		return 0;
	}

	if (argc != 2)
		return -EINVAL;

	if (!strcasecmp(argv[0], "hydration_threshold")) {
		if (kstrtouint(argv[1], 10, &value))
			return -EINVAL;

		set_hydration_threshold(clone, value);

		return 0;
	}

	if (!strcasecmp(argv[0], "hydration_batch_size")) {
		if (kstrtouint(argv[1], 10, &value))
			return -EINVAL;

		set_hydration_batch_size(clone, value);

		return 0;
	}

	DMERR("%s: Unsupported message `%s'", clone_device_name(clone), argv[0]);
	return -EINVAL;
}