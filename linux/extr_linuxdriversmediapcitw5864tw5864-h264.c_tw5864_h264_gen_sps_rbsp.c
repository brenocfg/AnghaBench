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
struct bs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_GOP_SIZE ; 
 int /*<<< orphan*/  bs_init (struct bs*,int /*<<< orphan*/ *,size_t) ; 
 int bs_len (struct bs*) ; 
 int /*<<< orphan*/  bs_rbsp_trailing (struct bs*) ; 
 int /*<<< orphan*/  bs_write (struct bs*,int,int) ; 
 int /*<<< orphan*/  bs_write_ue (struct bs*,int) ; 
 int ilog2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tw5864_h264_gen_sps_rbsp(u8 *buf, size_t size, int width, int height)
{
	struct bs bs, *s;

	s = &bs;
	bs_init(s, buf, size);
	bs_write(s, 8, 0x42); /* profile_idc, baseline */
	bs_write(s, 1, 1); /* constraint_set0_flag */
	bs_write(s, 1, 1); /* constraint_set1_flag */
	bs_write(s, 1, 0); /* constraint_set2_flag */
	bs_write(s, 5, 0); /* reserved_zero_5bits */
	bs_write(s, 8, 0x1e); /* level_idc */
	bs_write_ue(s, 0); /* seq_parameter_set_id */
	bs_write_ue(s, ilog2(MAX_GOP_SIZE) - 4); /* log2_max_frame_num_minus4 */
	bs_write_ue(s, 0); /* pic_order_cnt_type */
	/* log2_max_pic_order_cnt_lsb_minus4 */
	bs_write_ue(s, ilog2(MAX_GOP_SIZE) - 4);
	bs_write_ue(s, 1); /* num_ref_frames */
	bs_write(s, 1, 0); /* gaps_in_frame_num_value_allowed_flag */
	bs_write_ue(s, width / 16 - 1); /* pic_width_in_mbs_minus1 */
	bs_write_ue(s, height / 16 - 1); /* pic_height_in_map_units_minus1 */
	bs_write(s, 1, 1); /* frame_mbs_only_flag */
	bs_write(s, 1, 0); /* direct_8x8_inference_flag */
	bs_write(s, 1, 0); /* frame_cropping_flag */
	bs_write(s, 1, 0); /* vui_parameters_present_flag */
	bs_rbsp_trailing(s);
	return bs_len(s);
}