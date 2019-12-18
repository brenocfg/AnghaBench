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
struct s5p_mfc_ctx {struct s5p_mfc_dev* dev; } ;

/* Variables and functions */
 unsigned int OFFSETA (unsigned long) ; 
 int /*<<< orphan*/  S5P_FIMV_ENC_SI_CH0_SB_ADR ; 
 int /*<<< orphan*/  S5P_FIMV_ENC_SI_CH0_SB_SIZE ; 
 int /*<<< orphan*/  mfc_write (struct s5p_mfc_dev*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s5p_mfc_set_enc_stream_buffer_v5(struct s5p_mfc_ctx *ctx,
		unsigned long addr, unsigned int size)
{
	struct s5p_mfc_dev *dev = ctx->dev;

	mfc_write(dev, OFFSETA(addr), S5P_FIMV_ENC_SI_CH0_SB_ADR);
	mfc_write(dev, size, S5P_FIMV_ENC_SI_CH0_SB_SIZE);
	return 0;
}