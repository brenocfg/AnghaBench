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
struct s5p_mfc_regs {int /*<<< orphan*/  e_source_second_plane_addr; int /*<<< orphan*/  e_source_first_plane_addr; } ;
struct s5p_mfc_dev {struct s5p_mfc_regs* mfc_regs; } ;
struct s5p_mfc_ctx {struct s5p_mfc_dev* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  mfc_debug (int,char*,unsigned long) ; 
 int /*<<< orphan*/  writel (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void s5p_mfc_set_enc_frame_buffer_v6(struct s5p_mfc_ctx *ctx,
		unsigned long y_addr, unsigned long c_addr)
{
	struct s5p_mfc_dev *dev = ctx->dev;
	const struct s5p_mfc_regs *mfc_regs = dev->mfc_regs;

	writel(y_addr, mfc_regs->e_source_first_plane_addr);
	writel(c_addr, mfc_regs->e_source_second_plane_addr);

	mfc_debug(2, "enc src y buf addr: 0x%08lx\n", y_addr);
	mfc_debug(2, "enc src c buf addr: 0x%08lx\n", c_addr);
}