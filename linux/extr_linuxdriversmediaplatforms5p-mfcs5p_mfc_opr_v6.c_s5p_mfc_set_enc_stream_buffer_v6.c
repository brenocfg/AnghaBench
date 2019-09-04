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
struct s5p_mfc_regs {int /*<<< orphan*/  e_stream_buffer_size; int /*<<< orphan*/  e_stream_buffer_addr; } ;
struct s5p_mfc_dev {struct s5p_mfc_regs* mfc_regs; } ;
struct s5p_mfc_ctx {struct s5p_mfc_dev* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  mfc_debug (int,char*,unsigned long,unsigned int) ; 
 int /*<<< orphan*/  writel (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s5p_mfc_set_enc_stream_buffer_v6(struct s5p_mfc_ctx *ctx,
		unsigned long addr, unsigned int size)
{
	struct s5p_mfc_dev *dev = ctx->dev;
	const struct s5p_mfc_regs *mfc_regs = dev->mfc_regs;

	writel(addr, mfc_regs->e_stream_buffer_addr); /* 16B align */
	writel(size, mfc_regs->e_stream_buffer_size);

	mfc_debug(2, "stream buf addr: 0x%08lx, size: 0x%x\n",
		  addr, size);

	return 0;
}