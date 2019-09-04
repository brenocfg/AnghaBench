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
struct s5p_mfc_dev {unsigned long* dma_base; } ;
struct s5p_mfc_ctx {struct s5p_mfc_dev* dev; } ;

/* Variables and functions */
 size_t BANK_R_CTX ; 
 unsigned long MFC_OFFSET_SHIFT ; 
 int /*<<< orphan*/  S5P_FIMV_ENCODED_C_ADDR ; 
 int /*<<< orphan*/  S5P_FIMV_ENCODED_Y_ADDR ; 
 unsigned long mfc_read (struct s5p_mfc_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void s5p_mfc_get_enc_frame_buffer_v5(struct s5p_mfc_ctx *ctx,
		unsigned long *y_addr, unsigned long *c_addr)
{
	struct s5p_mfc_dev *dev = ctx->dev;

	*y_addr = dev->dma_base[BANK_R_CTX] +
		  (mfc_read(dev, S5P_FIMV_ENCODED_Y_ADDR) << MFC_OFFSET_SHIFT);
	*c_addr = dev->dma_base[BANK_R_CTX] +
		  (mfc_read(dev, S5P_FIMV_ENCODED_C_ADDR) << MFC_OFFSET_SHIFT);
}