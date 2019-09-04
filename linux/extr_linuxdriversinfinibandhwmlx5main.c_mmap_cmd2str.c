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
typedef  enum mlx5_ib_mmap_cmd { ____Placeholder_mlx5_ib_mmap_cmd } mlx5_ib_mmap_cmd ;

/* Variables and functions */
#define  MLX5_IB_MMAP_DEVICE_MEM 131 
#define  MLX5_IB_MMAP_NC_PAGE 130 
#define  MLX5_IB_MMAP_REGULAR_PAGE 129 
#define  MLX5_IB_MMAP_WC_PAGE 128 

__attribute__((used)) static inline char *mmap_cmd2str(enum mlx5_ib_mmap_cmd cmd)
{
	switch (cmd) {
	case MLX5_IB_MMAP_WC_PAGE:
		return "WC";
	case MLX5_IB_MMAP_REGULAR_PAGE:
		return "best effort WC";
	case MLX5_IB_MMAP_NC_PAGE:
		return "NC";
	case MLX5_IB_MMAP_DEVICE_MEM:
		return "Device Memory";
	default:
		return NULL;
	}
}