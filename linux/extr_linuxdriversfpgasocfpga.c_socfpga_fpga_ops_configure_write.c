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
struct socfpga_fpga_priv {int dummy; } ;
struct fpga_manager {struct socfpga_fpga_priv* priv; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int /*<<< orphan*/  socfpga_fpga_data_writel (struct socfpga_fpga_priv*,int) ; 

__attribute__((used)) static int socfpga_fpga_ops_configure_write(struct fpga_manager *mgr,
					    const char *buf, size_t count)
{
	struct socfpga_fpga_priv *priv = mgr->priv;
	u32 *buffer_32 = (u32 *)buf;
	size_t i = 0;

	if (count <= 0)
		return -EINVAL;

	/* Write out the complete 32-bit chunks. */
	while (count >= sizeof(u32)) {
		socfpga_fpga_data_writel(priv, buffer_32[i++]);
		count -= sizeof(u32);
	}

	/* Write out remaining non 32-bit chunks. */
	switch (count) {
	case 3:
		socfpga_fpga_data_writel(priv, buffer_32[i++] & 0x00ffffff);
		break;
	case 2:
		socfpga_fpga_data_writel(priv, buffer_32[i++] & 0x0000ffff);
		break;
	case 1:
		socfpga_fpga_data_writel(priv, buffer_32[i++] & 0x000000ff);
		break;
	case 0:
		break;
	default:
		/* This will never happen. */
		return -EFAULT;
	}

	return 0;
}