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
struct era {int dummy; } ;
struct dm_target {struct era* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*,...) ; 
 int EINVAL ; 
 int in_worker0 (struct era*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  metadata_checkpoint ; 
 int /*<<< orphan*/  metadata_drop_snap ; 
 int /*<<< orphan*/  metadata_take_snap ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 

__attribute__((used)) static int era_message(struct dm_target *ti, unsigned argc, char **argv,
		       char *result, unsigned maxlen)
{
	struct era *era = ti->private;

	if (argc != 1) {
		DMERR("incorrect number of message arguments");
		return -EINVAL;
	}

	if (!strcasecmp(argv[0], "checkpoint"))
		return in_worker0(era, metadata_checkpoint);

	if (!strcasecmp(argv[0], "take_metadata_snap"))
		return in_worker0(era, metadata_take_snap);

	if (!strcasecmp(argv[0], "drop_metadata_snap"))
		return in_worker0(era, metadata_drop_snap);

	DMERR("unsupported message '%s'", argv[0]);
	return -EINVAL;
}