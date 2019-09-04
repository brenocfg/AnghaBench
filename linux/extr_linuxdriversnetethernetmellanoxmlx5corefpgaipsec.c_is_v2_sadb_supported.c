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
struct mlx5_fpga_ipsec {int /*<<< orphan*/  caps; } ;

/* Variables and functions */
 scalar_t__ MLX5_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipsec_extended_cap ; 
 int /*<<< orphan*/  v2_command ; 

__attribute__((used)) static inline bool is_v2_sadb_supported(struct mlx5_fpga_ipsec *fipsec)
{
	if (MLX5_GET(ipsec_extended_cap, fipsec->caps, v2_command))
		return true;
	return false;
}