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
typedef  int /*<<< orphan*/  u16 ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCQI_INFO_TYPE_VERSION ; 
 int /*<<< orphan*/  MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcqi_version ; 
 int mlx5_reg_mcqi_query (struct mlx5_core_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlx5_reg_mcqi_version_query(struct mlx5_core_dev *dev,
				       u16 component_index, bool read_pending,
				       u32 *mcqi_version_out)
{
	return mlx5_reg_mcqi_query(dev, component_index, read_pending,
				   MCQI_INFO_TYPE_VERSION,
				   MLX5_ST_SZ_BYTES(mcqi_version),
				   mcqi_version_out);
}