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
typedef  int u32 ;
struct sun4i_csi {scalar_t__ regs; } ;

/* Variables and functions */
 int CSI_BUF_CTRL_DBS ; 
 scalar_t__ CSI_BUF_CTRL_REG ; 
 int readl (scalar_t__) ; 
 int sun4i_csi_buffer_fill_slot (struct sun4i_csi*,unsigned int) ; 
 int /*<<< orphan*/  sun4i_csi_buffer_mark_done (struct sun4i_csi*,unsigned int,unsigned int) ; 

__attribute__((used)) static int sun4i_csi_buffer_flip(struct sun4i_csi *csi, unsigned int sequence)
{
	u32 reg = readl(csi->regs + CSI_BUF_CTRL_REG);
	unsigned int next;

	/* Our next buffer is not the current buffer */
	next = !(reg & CSI_BUF_CTRL_DBS);

	/* Report the previous buffer as done */
	sun4i_csi_buffer_mark_done(csi, next, sequence);

	/* Put a new buffer in there */
	return sun4i_csi_buffer_fill_slot(csi, next);
}