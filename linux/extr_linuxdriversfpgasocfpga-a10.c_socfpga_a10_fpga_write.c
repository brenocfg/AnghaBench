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
struct fpga_manager {struct a10_fpga_priv* priv; } ;
struct a10_fpga_priv {int /*<<< orphan*/  fpga_data_addr; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int socfpga_a10_fpga_write(struct fpga_manager *mgr, const char *buf,
				  size_t count)
{
	struct a10_fpga_priv *priv = mgr->priv;
	u32 *buffer_32 = (u32 *)buf;
	size_t i = 0;

	if (count <= 0)
		return -EINVAL;

	/* Write out the complete 32-bit chunks */
	while (count >= sizeof(u32)) {
		writel(buffer_32[i++], priv->fpga_data_addr);
		count -= sizeof(u32);
	}

	/* Write out remaining non 32-bit chunks */
	switch (count) {
	case 3:
		writel(buffer_32[i++] & 0x00ffffff, priv->fpga_data_addr);
		break;
	case 2:
		writel(buffer_32[i++] & 0x0000ffff, priv->fpga_data_addr);
		break;
	case 1:
		writel(buffer_32[i++] & 0x000000ff, priv->fpga_data_addr);
		break;
	case 0:
		break;
	default:
		/* This will never happen */
		return -EFAULT;
	}

	return 0;
}