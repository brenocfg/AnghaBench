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
struct ivtv {int* last_dec_timing; int /*<<< orphan*/  i_flags; int /*<<< orphan*/  decoding; } ;
typedef  int s64 ;

/* Variables and functions */
 int /*<<< orphan*/  CX2341X_DEC_GET_TIMING_INFO ; 
 int CX2341X_MBOX_MAX_DATA ; 
 int EIO ; 
 int /*<<< orphan*/  IVTV_DEBUG_WARN (char*) ; 
 int /*<<< orphan*/  IVTV_F_I_VALID_DEC_TIMINGS ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ ivtv_api (struct ivtv*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int ivtv_g_pts_frame(struct ivtv *itv, s64 *pts, s64 *frame)
{
	u32 data[CX2341X_MBOX_MAX_DATA];

	if (test_bit(IVTV_F_I_VALID_DEC_TIMINGS, &itv->i_flags)) {
		*pts = (s64)((u64)itv->last_dec_timing[2] << 32) |
			(u64)itv->last_dec_timing[1];
		*frame = itv->last_dec_timing[0];
		return 0;
	}
	*pts = 0;
	*frame = 0;
	if (atomic_read(&itv->decoding)) {
		if (ivtv_api(itv, CX2341X_DEC_GET_TIMING_INFO, 5, data)) {
			IVTV_DEBUG_WARN("GET_TIMING: couldn't read clock\n");
			return -EIO;
		}
		memcpy(itv->last_dec_timing, data, sizeof(itv->last_dec_timing));
		set_bit(IVTV_F_I_VALID_DEC_TIMINGS, &itv->i_flags);
		*pts = (s64)((u64) data[2] << 32) | (u64) data[1];
		*frame = data[0];
		/*timing->scr = (u64) (((u64) data[4] << 32) | (u64) (data[3]));*/
	}
	return 0;
}