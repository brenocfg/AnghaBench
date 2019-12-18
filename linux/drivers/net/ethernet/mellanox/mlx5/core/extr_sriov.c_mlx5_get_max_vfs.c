#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct mlx5_core_dev {int /*<<< orphan*/  pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  host_total_vfs; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/  const*) ; 
 scalar_t__ MLX5_GET (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 TYPE_1__ host_params_context ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/  const*) ; 
 scalar_t__ mlx5_core_is_ecpf_esw_manager (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/ * mlx5_esw_query_functions (struct mlx5_core_dev*) ; 
 scalar_t__ pci_sriov_get_totalvfs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  query_esw_functions_out ; 

__attribute__((used)) static u16 mlx5_get_max_vfs(struct mlx5_core_dev *dev)
{
	u16 host_total_vfs;
	const u32 *out;

	if (mlx5_core_is_ecpf_esw_manager(dev)) {
		out = mlx5_esw_query_functions(dev);

		/* Old FW doesn't support getting total_vfs from esw func
		 * but supports getting it from pci_sriov.
		 */
		if (IS_ERR(out))
			goto done;
		host_total_vfs = MLX5_GET(query_esw_functions_out, out,
					  host_params_context.host_total_vfs);
		kvfree(out);
		if (host_total_vfs)
			return host_total_vfs;
	}

done:
	return pci_sriov_get_totalvfs(dev->pdev);
}