#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct v4l2_enc_idx_entry {int flags; } ;
struct v4l2_enc_idx {int entries; int entries_cap; struct v4l2_enc_idx_entry* entry; } ;
struct ivtv {int pgm_info_write_idx; int pgm_info_read_idx; struct v4l2_enc_idx_entry* pgm_info; int /*<<< orphan*/  capturing; } ;
struct file {int dummy; } ;
struct TYPE_2__ {struct ivtv* itv; } ;

/* Variables and functions */
 int IVTV_MAX_PGM_INDEX ; 
 int V4L2_ENC_IDX_ENTRIES ; 
 int V4L2_ENC_IDX_FRAME_B ; 
 int V4L2_ENC_IDX_FRAME_MASK ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 TYPE_1__* fh2id (void*) ; 

__attribute__((used)) static int ivtv_g_enc_index(struct file *file, void *fh, struct v4l2_enc_idx *idx)
{
	struct ivtv *itv = fh2id(fh)->itv;
	struct v4l2_enc_idx_entry *e = idx->entry;
	int entries;
	int i;

	entries = (itv->pgm_info_write_idx + IVTV_MAX_PGM_INDEX - itv->pgm_info_read_idx) %
				IVTV_MAX_PGM_INDEX;
	if (entries > V4L2_ENC_IDX_ENTRIES)
		entries = V4L2_ENC_IDX_ENTRIES;
	idx->entries = 0;
	idx->entries_cap = IVTV_MAX_PGM_INDEX;
	if (!atomic_read(&itv->capturing))
		return 0;
	for (i = 0; i < entries; i++) {
		*e = itv->pgm_info[(itv->pgm_info_read_idx + i) % IVTV_MAX_PGM_INDEX];
		if ((e->flags & V4L2_ENC_IDX_FRAME_MASK) <= V4L2_ENC_IDX_FRAME_B) {
			idx->entries++;
			e++;
		}
	}
	itv->pgm_info_read_idx = (itv->pgm_info_read_idx + idx->entries) % IVTV_MAX_PGM_INDEX;
	return 0;
}