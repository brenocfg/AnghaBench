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
struct switch_ctx {unsigned long nr_regions; unsigned long nr_paths; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMWARN (char*,...) ; 
 int EINVAL ; 
 unsigned long parse_hex (char const**) ; 
 unsigned long switch_region_table_read (struct switch_ctx*,unsigned long) ; 
 int /*<<< orphan*/  switch_region_table_write (struct switch_ctx*,unsigned long,unsigned long) ; 
 scalar_t__ unlikely (char const) ; 

__attribute__((used)) static int process_set_region_mappings(struct switch_ctx *sctx,
				       unsigned argc, char **argv)
{
	unsigned i;
	unsigned long region_index = 0;

	for (i = 1; i < argc; i++) {
		unsigned long path_nr;
		const char *string = argv[i];

		if ((*string & 0xdf) == 'R') {
			unsigned long cycle_length, num_write;

			string++;
			if (unlikely(*string == ',')) {
				DMWARN("invalid set_region_mappings argument: '%s'", argv[i]);
				return -EINVAL;
			}
			cycle_length = parse_hex(&string);
			if (unlikely(*string != ',')) {
				DMWARN("invalid set_region_mappings argument: '%s'", argv[i]);
				return -EINVAL;
			}
			string++;
			if (unlikely(!*string)) {
				DMWARN("invalid set_region_mappings argument: '%s'", argv[i]);
				return -EINVAL;
			}
			num_write = parse_hex(&string);
			if (unlikely(*string)) {
				DMWARN("invalid set_region_mappings argument: '%s'", argv[i]);
				return -EINVAL;
			}

			if (unlikely(!cycle_length) || unlikely(cycle_length - 1 > region_index)) {
				DMWARN("invalid set_region_mappings cycle length: %lu > %lu",
				       cycle_length - 1, region_index);
				return -EINVAL;
			}
			if (unlikely(region_index + num_write < region_index) ||
			    unlikely(region_index + num_write >= sctx->nr_regions)) {
				DMWARN("invalid set_region_mappings region number: %lu + %lu >= %lu",
				       region_index, num_write, sctx->nr_regions);
				return -EINVAL;
			}

			while (num_write--) {
				region_index++;
				path_nr = switch_region_table_read(sctx, region_index - cycle_length);
				switch_region_table_write(sctx, region_index, path_nr);
			}

			continue;
		}

		if (*string == ':')
			region_index++;
		else {
			region_index = parse_hex(&string);
			if (unlikely(*string != ':')) {
				DMWARN("invalid set_region_mappings argument: '%s'", argv[i]);
				return -EINVAL;
			}
		}

		string++;
		if (unlikely(!*string)) {
			DMWARN("invalid set_region_mappings argument: '%s'", argv[i]);
			return -EINVAL;
		}

		path_nr = parse_hex(&string);
		if (unlikely(*string)) {
			DMWARN("invalid set_region_mappings argument: '%s'", argv[i]);
			return -EINVAL;
		}
		if (unlikely(region_index >= sctx->nr_regions)) {
			DMWARN("invalid set_region_mappings region number: %lu >= %lu", region_index, sctx->nr_regions);
			return -EINVAL;
		}
		if (unlikely(path_nr >= sctx->nr_paths)) {
			DMWARN("invalid set_region_mappings device: %lu >= %u", path_nr, sctx->nr_paths);
			return -EINVAL;
		}

		switch_region_table_write(sctx, region_index, path_nr);
	}

	return 0;
}