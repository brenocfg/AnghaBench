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
typedef  int u8 ;
struct bs {int bits_left; int* ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_GOP_SIZE ; 
 int /*<<< orphan*/  bs_init (struct bs*,int*,size_t) ; 
 int bs_len (struct bs*) ; 
 int /*<<< orphan*/  bs_write (struct bs*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  bs_write1 (struct bs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bs_write_se (struct bs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bs_write_ue (struct bs*,unsigned int) ; 
 int /*<<< orphan*/  ilog2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tw5864_h264_gen_slice_head(u8 *buf, size_t size,
				      unsigned int idr_pic_id,
				      unsigned int frame_gop_seqno,
				      int *tail_nb_bits, u8 *tail)
{
	struct bs bs, *s;
	int is_i_frame = frame_gop_seqno == 0;

	s = &bs;
	bs_init(s, buf, size);
	bs_write_ue(s, 0); /* first_mb_in_slice */
	bs_write_ue(s, is_i_frame ? 2 : 5); /* slice_type - I or P */
	bs_write_ue(s, 0); /* pic_parameter_set_id */
	bs_write(s, ilog2(MAX_GOP_SIZE), frame_gop_seqno); /* frame_num */
	if (is_i_frame)
		bs_write_ue(s, idr_pic_id);

	/* pic_order_cnt_lsb */
	bs_write(s, ilog2(MAX_GOP_SIZE), frame_gop_seqno);

	if (is_i_frame) {
		bs_write1(s, 0); /* no_output_of_prior_pics_flag */
		bs_write1(s, 0); /* long_term_reference_flag */
	} else {
		bs_write1(s, 0); /* num_ref_idx_active_override_flag */
		bs_write1(s, 0); /* ref_pic_list_reordering_flag_l0 */
		bs_write1(s, 0); /* adaptive_ref_pic_marking_mode_flag */
	}

	bs_write_se(s, 0); /* slice_qp_delta */

	if (s->bits_left != 8) {
		*tail = ((s->ptr[0]) << s->bits_left);
		*tail_nb_bits = 8 - s->bits_left;
	} else {
		*tail = 0;
		*tail_nb_bits = 0;
	}

	return bs_len(s);
}