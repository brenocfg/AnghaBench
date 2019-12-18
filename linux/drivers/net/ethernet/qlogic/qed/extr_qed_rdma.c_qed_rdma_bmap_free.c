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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
struct qed_hwfn {int dummy; } ;
struct qed_bmap {unsigned long* bitmap; int max_count; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*,int,...) ; 
 int bitmap_weight (unsigned long*,int) ; 
 int /*<<< orphan*/  kfree (unsigned long*) ; 
 int sprintf (int /*<<< orphan*/ *,char*,int) ; 

void qed_rdma_bmap_free(struct qed_hwfn *p_hwfn,
			struct qed_bmap *bmap, bool check)
{
	int weight = bitmap_weight(bmap->bitmap, bmap->max_count);
	int last_line = bmap->max_count / (64 * 8);
	int last_item = last_line * 8 +
	    DIV_ROUND_UP(bmap->max_count % (64 * 8), 64);
	u64 *pmap = (u64 *)bmap->bitmap;
	int line, item, offset;
	u8 str_last_line[200] = { 0 };

	if (!weight || !check)
		goto end;

	DP_NOTICE(p_hwfn,
		  "%s bitmap not free - size=%d, weight=%d, 512 bits per line\n",
		  bmap->name, bmap->max_count, weight);

	/* print aligned non-zero lines, if any */
	for (item = 0, line = 0; line < last_line; line++, item += 8)
		if (bitmap_weight((unsigned long *)&pmap[item], 64 * 8))
			DP_NOTICE(p_hwfn,
				  "line 0x%04x: 0x%016llx 0x%016llx 0x%016llx 0x%016llx 0x%016llx 0x%016llx 0x%016llx 0x%016llx\n",
				  line,
				  pmap[item],
				  pmap[item + 1],
				  pmap[item + 2],
				  pmap[item + 3],
				  pmap[item + 4],
				  pmap[item + 5],
				  pmap[item + 6], pmap[item + 7]);

	/* print last unaligned non-zero line, if any */
	if ((bmap->max_count % (64 * 8)) &&
	    (bitmap_weight((unsigned long *)&pmap[item],
			   bmap->max_count - item * 64))) {
		offset = sprintf(str_last_line, "line 0x%04x: ", line);
		for (; item < last_item; item++)
			offset += sprintf(str_last_line + offset,
					  "0x%016llx ", pmap[item]);
		DP_NOTICE(p_hwfn, "%s\n", str_last_line);
	}

end:
	kfree(bmap->bitmap);
	bmap->bitmap = NULL;
}