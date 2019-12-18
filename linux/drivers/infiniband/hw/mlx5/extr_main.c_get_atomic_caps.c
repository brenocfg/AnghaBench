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
typedef  int u8 ;
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;
struct ib_device_attr {int /*<<< orphan*/  atomic_cap; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_ATOMIC_HCA ; 
 int /*<<< orphan*/  IB_ATOMIC_NONE ; 
 int MLX5_ATOMIC_OPS_CMP_SWAP ; 
 int MLX5_ATOMIC_OPS_FETCH_ADD ; 
 int MLX5_ATOMIC_SIZE_QP_8BYTES ; 
 int MLX5_CAP_ATOMIC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int atomic_operations ; 
 int atomic_req_8B_endianness_mode ; 

__attribute__((used)) static void get_atomic_caps(struct mlx5_ib_dev *dev,
			    u8 atomic_size_qp,
			    struct ib_device_attr *props)
{
	u8 tmp;
	u8 atomic_operations = MLX5_CAP_ATOMIC(dev->mdev, atomic_operations);
	u8 atomic_req_8B_endianness_mode =
		MLX5_CAP_ATOMIC(dev->mdev, atomic_req_8B_endianness_mode);

	/* Check if HW supports 8 bytes standard atomic operations and capable
	 * of host endianness respond
	 */
	tmp = MLX5_ATOMIC_OPS_CMP_SWAP | MLX5_ATOMIC_OPS_FETCH_ADD;
	if (((atomic_operations & tmp) == tmp) &&
	    (atomic_size_qp & MLX5_ATOMIC_SIZE_QP_8BYTES) &&
	    (atomic_req_8B_endianness_mode)) {
		props->atomic_cap = IB_ATOMIC_HCA;
	} else {
		props->atomic_cap = IB_ATOMIC_NONE;
	}
}