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
struct parsed_partitions {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */

__attribute__((used)) static void parse_minix(struct parsed_partitions *state,
			sector_t offset, sector_t size, int origin)
{
#ifdef CONFIG_MINIX_SUBPARTITION
	Sector sect;
	unsigned char *data;
	struct partition *p;
	int i;

	data = read_part_sector(state, offset, &sect);
	if (!data)
		return;

	p = (struct partition *)(data + 0x1be);

	/* The first sector of a Minix partition can have either
	 * a secondary MBR describing its subpartitions, or
	 * the normal boot sector. */
	if (msdos_magic_present(data + 510) &&
	    SYS_IND(p) == MINIX_PARTITION) { /* subpartition table present */
		char tmp[1 + BDEVNAME_SIZE + 10 + 9 + 1];

		snprintf(tmp, sizeof(tmp), " %s%d: <minix:", state->name, origin);
		strlcat(state->pp_buf, tmp, PAGE_SIZE);
		for (i = 0; i < MINIX_NR_SUBPARTITIONS; i++, p++) {
			if (state->next == state->limit)
				break;
			/* add each partition in use */
			if (SYS_IND(p) == MINIX_PARTITION)
				put_partition(state, state->next++,
					      start_sect(p), nr_sects(p));
		}
		strlcat(state->pp_buf, " >\n", PAGE_SIZE);
	}
	put_dev_sector(sect);
#endif /* CONFIG_MINIX_SUBPARTITION */
}