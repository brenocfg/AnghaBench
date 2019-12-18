#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct mlx5_ib_sq {int /*<<< orphan*/  tisn; } ;
struct mlx5_core_dev {int dummy; } ;
struct ib_pd {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  lag_tx_port_affinity; } ;
struct TYPE_3__ {int uid; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* MLX5_ADDR_OF (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_SET (void*,void*,int /*<<< orphan*/ ,int) ; 
 int MLX5_ST_SZ_BYTES (void*) ; 
 TYPE_2__ bitmask ; 
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  kvfree (void*) ; 
 void* kvzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lag_tx_port_affinity ; 
 int mlx5_core_modify_tis (struct mlx5_core_dev*,int /*<<< orphan*/ ,void*,int) ; 
 void* modify_tis_in ; 
 TYPE_1__* to_mpd (struct ib_pd*) ; 
 int /*<<< orphan*/  uid ; 

__attribute__((used)) static int modify_raw_packet_tx_affinity(struct mlx5_core_dev *dev,
					 struct mlx5_ib_sq *sq, u8 tx_affinity,
					 struct ib_pd *pd)
{
	void *in;
	void *tisc;
	int inlen;
	int err;

	inlen = MLX5_ST_SZ_BYTES(modify_tis_in);
	in = kvzalloc(inlen, GFP_KERNEL);
	if (!in)
		return -ENOMEM;

	MLX5_SET(modify_tis_in, in, bitmask.lag_tx_port_affinity, 1);
	MLX5_SET(modify_tis_in, in, uid, to_mpd(pd)->uid);

	tisc = MLX5_ADDR_OF(modify_tis_in, in, ctx);
	MLX5_SET(tisc, tisc, lag_tx_port_affinity, tx_affinity);

	err = mlx5_core_modify_tis(dev, sq->tisn, in, inlen);

	kvfree(in);

	return err;
}