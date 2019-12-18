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
struct switch_path {int dummy; } ;
struct switch_ctx {int dummy; } ;
struct dm_target {char* error; int num_discard_bios; } ;
struct dm_arg_set {unsigned int argc; char** argv; } ;
struct dm_arg {int member_0; int member_1; char* member_2; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
#define  KMALLOC_MAX_SIZE 129 
#define  UINT_MAX 128 
 int alloc_region_table (struct dm_target*,unsigned int) ; 
 struct switch_ctx* alloc_switch_ctx (struct dm_target*,unsigned int,unsigned int) ; 
 int dm_read_arg (struct dm_arg const*,struct dm_arg_set*,unsigned int*,char**) ; 
 int dm_read_arg_group (struct dm_arg const*,struct dm_arg_set*,unsigned int*,char**) ; 
 int dm_set_target_max_io_len (struct dm_target*,unsigned int) ; 
 int /*<<< orphan*/  initialise_region_table (struct switch_ctx*) ; 
 int parse_path (struct dm_arg_set*,struct dm_target*) ; 
 int /*<<< orphan*/  switch_dtr (struct dm_target*) ; 

__attribute__((used)) static int switch_ctr(struct dm_target *ti, unsigned argc, char **argv)
{
	static const struct dm_arg _args[] = {
		{1, (KMALLOC_MAX_SIZE - sizeof(struct switch_ctx)) / sizeof(struct switch_path), "Invalid number of paths"},
		{1, UINT_MAX, "Invalid region size"},
		{0, 0, "Invalid number of optional args"},
	};

	struct switch_ctx *sctx;
	struct dm_arg_set as;
	unsigned nr_paths, region_size, nr_optional_args;
	int r;

	as.argc = argc;
	as.argv = argv;

	r = dm_read_arg(_args, &as, &nr_paths, &ti->error);
	if (r)
		return -EINVAL;

	r = dm_read_arg(_args + 1, &as, &region_size, &ti->error);
	if (r)
		return r;

	r = dm_read_arg_group(_args + 2, &as, &nr_optional_args, &ti->error);
	if (r)
		return r;
	/* parse optional arguments here, if we add any */

	if (as.argc != nr_paths * 2) {
		ti->error = "Incorrect number of path arguments";
		return -EINVAL;
	}

	sctx = alloc_switch_ctx(ti, nr_paths, region_size);
	if (!sctx) {
		ti->error = "Cannot allocate redirection context";
		return -ENOMEM;
	}

	r = dm_set_target_max_io_len(ti, region_size);
	if (r)
		goto error;

	while (as.argc) {
		r = parse_path(&as, ti);
		if (r)
			goto error;
	}

	r = alloc_region_table(ti, nr_paths);
	if (r)
		goto error;

	initialise_region_table(sctx);

	/* For UNMAP, sending the request down any path is sufficient */
	ti->num_discard_bios = 1;

	return 0;

error:
	switch_dtr(ti);

	return r;
}