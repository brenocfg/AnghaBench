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
typedef  int u64 ;
typedef  int u32 ;
struct v4l2_enc_idx_entry {int offset; int length; int pts; int flags; } ;
struct ivtv {int pgm_info_offset; int pgm_info_num; int pgm_info_write_idx; scalar_t__ mpg_data_received; scalar_t__ vbi_data_inserted; struct v4l2_enc_idx_entry* pgm_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  IVTV_DEBUG_WARN (char*,int,int) ; 
 int V4L2_ENC_IDX_FRAME_B ; 
 int V4L2_ENC_IDX_FRAME_I ; 
 int V4L2_ENC_IDX_FRAME_P ; 
 int read_enc (int) ; 

__attribute__((used)) static void ivtv_update_pgm_info(struct ivtv *itv)
{
	u32 wr_idx = (read_enc(itv->pgm_info_offset) - itv->pgm_info_offset - 4) / 24;
	int cnt;
	int i = 0;

	if (wr_idx >= itv->pgm_info_num) {
		IVTV_DEBUG_WARN("Invalid PGM index %d (>= %d)\n", wr_idx, itv->pgm_info_num);
		return;
	}
	cnt = (wr_idx + itv->pgm_info_num - itv->pgm_info_write_idx) % itv->pgm_info_num;
	while (i < cnt) {
		int idx = (itv->pgm_info_write_idx + i) % itv->pgm_info_num;
		struct v4l2_enc_idx_entry *e = itv->pgm_info + idx;
		u32 addr = itv->pgm_info_offset + 4 + idx * 24;
		const int mapping[8] = { -1, V4L2_ENC_IDX_FRAME_I, V4L2_ENC_IDX_FRAME_P, -1,
			V4L2_ENC_IDX_FRAME_B, -1, -1, -1 };
					// 1=I, 2=P, 4=B

		e->offset = read_enc(addr + 4) + ((u64)read_enc(addr + 8) << 32);
		if (e->offset > itv->mpg_data_received) {
			break;
		}
		e->offset += itv->vbi_data_inserted;
		e->length = read_enc(addr);
		e->pts = read_enc(addr + 16) + ((u64)(read_enc(addr + 20) & 1) << 32);
		e->flags = mapping[read_enc(addr + 12) & 7];
		i++;
	}
	itv->pgm_info_write_idx = (itv->pgm_info_write_idx + i) % itv->pgm_info_num;
}