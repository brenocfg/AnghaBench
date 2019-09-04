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
struct fpga_manager {struct alt_pr_priv* priv; } ;
struct alt_pr_priv {int /*<<< orphan*/  reg_base; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int EIO ; 
 scalar_t__ FPGA_MGR_STATE_WRITE_ERR ; 
 scalar_t__ alt_pr_fpga_state (struct fpga_manager*) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int alt_pr_fpga_write(struct fpga_manager *mgr, const char *buf,
			     size_t count)
{
	struct alt_pr_priv *priv = mgr->priv;
	u32 *buffer_32 = (u32 *)buf;
	size_t i = 0;

	if (count <= 0)
		return -EINVAL;

	/* Write out the complete 32-bit chunks */
	while (count >= sizeof(u32)) {
		writel(buffer_32[i++], priv->reg_base);
		count -= sizeof(u32);
	}

	/* Write out remaining non 32-bit chunks */
	switch (count) {
	case 3:
		writel(buffer_32[i++] & 0x00ffffff, priv->reg_base);
		break;
	case 2:
		writel(buffer_32[i++] & 0x0000ffff, priv->reg_base);
		break;
	case 1:
		writel(buffer_32[i++] & 0x000000ff, priv->reg_base);
		break;
	case 0:
		break;
	default:
		/* This will never happen */
		return -EFAULT;
	}

	if (alt_pr_fpga_state(mgr) == FPGA_MGR_STATE_WRITE_ERR)
		return -EIO;

	return 0;
}