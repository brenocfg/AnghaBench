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
 int /*<<< orphan*/  bs_init (struct bs*,int /*<<< orphan*/ *,size_t) ; 
 int bs_len (struct bs*) ; 
 int /*<<< orphan*/  bs_rbsp_trailing (struct bs*) ; 
 int /*<<< orphan*/  bs_write (struct bs*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bs_write_se (struct bs*,int) ; 
 int /*<<< orphan*/  bs_write_ue (struct bs*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tw5864_h264_gen_pps_rbsp(u8 *buf, size_t size, int qp)
{
	struct bs bs, *s;

	s = &bs;
	bs_init(s, buf, size);
	bs_write_ue(s, 0); /* pic_parameter_set_id */
	bs_write_ue(s, 0); /* seq_parameter_set_id */
	bs_write(s, 1, 0); /* entropy_coding_mode_flag */
	bs_write(s, 1, 0); /* pic_order_present_flag */
	bs_write_ue(s, 0); /* num_slice_groups_minus1 */
	bs_write_ue(s, 0); /* i_num_ref_idx_l0_active_minus1 */
	bs_write_ue(s, 0); /* i_num_ref_idx_l1_active_minus1 */
	bs_write(s, 1, 0); /* weighted_pred_flag */
	bs_write(s, 2, 0); /* weighted_bipred_idc */
	bs_write_se(s, qp - 26); /* pic_init_qp_minus26 */
	bs_write_se(s, qp - 26); /* pic_init_qs_minus26 */
	bs_write_se(s, 0); /* chroma_qp_index_offset */
	bs_write(s, 1, 0); /* deblocking_filter_control_present_flag */
	bs_write(s, 1, 0); /* constrained_intra_pred_flag */
	bs_write(s, 1, 0); /* redundant_pic_cnt_present_flag */
	bs_rbsp_trailing(s);
	return bs_len(s);
}