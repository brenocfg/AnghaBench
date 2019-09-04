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

/* Variables and functions */
 int /*<<< orphan*/  pr_warn (char*) ; 

__attribute__((used)) static int mlx5_mtu_to_ib_mtu(int mtu)
{
	switch (mtu) {
	case 256: return 1;
	case 512: return 2;
	case 1024: return 3;
	case 2048: return 4;
	case 4096: return 5;
	default:
		pr_warn("invalid mtu\n");
		return -1;
	}
}