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
typedef  int /*<<< orphan*/  u32 ;
struct mlx5_core_dev {int dummy; } ;
typedef  int /*<<< orphan*/  out ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MLX5_ST_SZ_DW (int /*<<< orphan*/ ) ; 
 int mlx5_query_pfcc_reg (struct mlx5_core_dev*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pfcc_reg ; 
 int /*<<< orphan*/  pprx ; 
 int /*<<< orphan*/  pptx ; 

int mlx5_query_port_pause(struct mlx5_core_dev *dev,
			  u32 *rx_pause, u32 *tx_pause)
{
	u32 out[MLX5_ST_SZ_DW(pfcc_reg)];
	int err;

	err = mlx5_query_pfcc_reg(dev, out, sizeof(out));
	if (err)
		return err;

	if (rx_pause)
		*rx_pause = MLX5_GET(pfcc_reg, out, pprx);

	if (tx_pause)
		*tx_pause = MLX5_GET(pfcc_reg, out, pptx);

	return 0;
}