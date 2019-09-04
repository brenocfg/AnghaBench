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

__attribute__((used)) static void parse_unixware(struct parsed_partitions *state,
			   sector_t offset, sector_t size, int origin)
{
#ifdef CONFIG_UNIXWARE_DISKLABEL
	Sector sect;
	struct unixware_disklabel *l;
	struct unixware_slice *p;

	l = read_part_sector(state, offset + 29, &sect);
	if (!l)
		return;
	if (le32_to_cpu(l->d_magic) != UNIXWARE_DISKMAGIC ||
	    le32_to_cpu(l->vtoc.v_magic) != UNIXWARE_DISKMAGIC2) {
		put_dev_sector(sect);
		return;
	}
	{
		char tmp[1 + BDEVNAME_SIZE + 10 + 12 + 1];

		snprintf(tmp, sizeof(tmp), " %s%d: <unixware:", state->name, origin);
		strlcat(state->pp_buf, tmp, PAGE_SIZE);
	}
	p = &l->vtoc.v_slice[1];
	/* I omit the 0th slice as it is the same as whole disk. */
	while (p - &l->vtoc.v_slice[0] < UNIXWARE_NUMSLICE) {
		if (state->next == state->limit)
			break;

		if (p->s_label != UNIXWARE_FS_UNUSED)
			put_partition(state, state->next++,
				      le32_to_cpu(p->start_sect),
				      le32_to_cpu(p->nr_sects));
		p++;
	}
	put_dev_sector(sect);
	strlcat(state->pp_buf, " >\n", PAGE_SIZE);
#endif
}