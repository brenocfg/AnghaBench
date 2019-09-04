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
struct mlx5_eqe {int sub_type; } ;
struct mlx5_core_dev {int /*<<< orphan*/  (* event ) (struct mlx5_core_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_DEV_EVENT_DELAY_DROP_TIMEOUT ; 
#define  MLX5_GENERAL_SUBTYPE_DELAY_DROP_TIMEOUT 128 
 int /*<<< orphan*/  mlx5_core_dbg (struct mlx5_core_dev*,char*,int) ; 
 int /*<<< orphan*/  stub1 (struct mlx5_core_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void general_event_handler(struct mlx5_core_dev *dev,
				  struct mlx5_eqe *eqe)
{
	switch (eqe->sub_type) {
	case MLX5_GENERAL_SUBTYPE_DELAY_DROP_TIMEOUT:
		if (dev->event)
			dev->event(dev, MLX5_DEV_EVENT_DELAY_DROP_TIMEOUT, 0);
		break;
	default:
		mlx5_core_dbg(dev, "General event with unrecognized subtype: sub_type %d\n",
			      eqe->sub_type);
	}
}