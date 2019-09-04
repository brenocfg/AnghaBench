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
struct unstripe_c {int stripes; int chunk_size; int unstripe; unsigned long long physical_start; int unstripe_offset; int unstripe_width; scalar_t__ chunk_shift; int /*<<< orphan*/  dev; } ;
struct dm_target {char* error; unsigned long long len; struct unstripe_c* private; int /*<<< orphan*/  table; } ;
typedef  unsigned long long sector_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cleanup_unstripe (struct unstripe_c*,struct dm_target*) ; 
 scalar_t__ dm_get_device (struct dm_target*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ dm_set_target_max_io_len (struct dm_target*,int) ; 
 int /*<<< orphan*/  dm_table_get_mode (int /*<<< orphan*/ ) ; 
 scalar_t__ fls (int) ; 
 scalar_t__ is_power_of_2 (int) ; 
 scalar_t__ kstrtouint (char*,int,int*) ; 
 struct unstripe_c* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ sector_div (unsigned long long,int) ; 
 int sscanf (char*,char*,unsigned long long*,char*) ; 

__attribute__((used)) static int unstripe_ctr(struct dm_target *ti, unsigned int argc, char **argv)
{
	struct unstripe_c *uc;
	sector_t tmp_len;
	unsigned long long start;
	char dummy;

	if (argc != 5) {
		ti->error = "Invalid number of arguments";
		return -EINVAL;
	}

	uc = kzalloc(sizeof(*uc), GFP_KERNEL);
	if (!uc) {
		ti->error = "Memory allocation for unstriped context failed";
		return -ENOMEM;
	}

	if (kstrtouint(argv[0], 10, &uc->stripes) || !uc->stripes) {
		ti->error = "Invalid stripe count";
		goto err;
	}

	if (kstrtouint(argv[1], 10, &uc->chunk_size) || !uc->chunk_size) {
		ti->error = "Invalid chunk_size";
		goto err;
	}

	if (kstrtouint(argv[2], 10, &uc->unstripe)) {
		ti->error = "Invalid stripe number";
		goto err;
	}

	if (uc->unstripe > uc->stripes && uc->stripes > 1) {
		ti->error = "Please provide stripe between [0, # of stripes]";
		goto err;
	}

	if (dm_get_device(ti, argv[3], dm_table_get_mode(ti->table), &uc->dev)) {
		ti->error = "Couldn't get striped device";
		goto err;
	}

	if (sscanf(argv[4], "%llu%c", &start, &dummy) != 1 || start != (sector_t)start) {
		ti->error = "Invalid striped device offset";
		goto err;
	}
	uc->physical_start = start;

	uc->unstripe_offset = uc->unstripe * uc->chunk_size;
	uc->unstripe_width = (uc->stripes - 1) * uc->chunk_size;
	uc->chunk_shift = is_power_of_2(uc->chunk_size) ? fls(uc->chunk_size) - 1 : 0;

	tmp_len = ti->len;
	if (sector_div(tmp_len, uc->chunk_size)) {
		ti->error = "Target length not divisible by chunk size";
		goto err;
	}

	if (dm_set_target_max_io_len(ti, uc->chunk_size)) {
		ti->error = "Failed to set max io len";
		goto err;
	}

	ti->private = uc;
	return 0;
err:
	cleanup_unstripe(uc, ti);
	return -EINVAL;
}