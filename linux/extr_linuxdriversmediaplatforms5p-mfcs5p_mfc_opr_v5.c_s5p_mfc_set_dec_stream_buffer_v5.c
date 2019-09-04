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
struct s5p_mfc_dev {int dummy; } ;
struct s5p_mfc_ctx {unsigned int dec_src_buf_size; struct s5p_mfc_dev* dev; } ;

/* Variables and functions */
 unsigned int OFFSETA (int) ; 
 int /*<<< orphan*/  S5P_FIMV_SI_CH0_CPB_SIZE ; 
 int /*<<< orphan*/  S5P_FIMV_SI_CH0_SB_FRM_SIZE ; 
 int /*<<< orphan*/  S5P_FIMV_SI_CH0_SB_ST_ADR ; 
 int /*<<< orphan*/  START_BYTE_NUM ; 
 int /*<<< orphan*/  mfc_write (struct s5p_mfc_dev*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s5p_mfc_write_info_v5 (struct s5p_mfc_ctx*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s5p_mfc_set_dec_stream_buffer_v5(struct s5p_mfc_ctx *ctx,
		int buf_addr, unsigned int start_num_byte,
		unsigned int buf_size)
{
	struct s5p_mfc_dev *dev = ctx->dev;

	mfc_write(dev, OFFSETA(buf_addr), S5P_FIMV_SI_CH0_SB_ST_ADR);
	mfc_write(dev, ctx->dec_src_buf_size, S5P_FIMV_SI_CH0_CPB_SIZE);
	mfc_write(dev, buf_size, S5P_FIMV_SI_CH0_SB_FRM_SIZE);
	s5p_mfc_write_info_v5(ctx, start_num_byte, START_BYTE_NUM);
	return 0;
}