#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_4__* vf_admin; } ;
struct TYPE_5__ {TYPE_3__ master; } ;
struct mlx4_priv {TYPE_1__ mfunc; } ;
struct mlx4_dev {int dummy; } ;
typedef  int /*<<< orphan*/  guid ;
typedef  int /*<<< orphan*/  __be64 ;
struct TYPE_8__ {TYPE_2__* vport; } ;
struct TYPE_6__ {int /*<<< orphan*/  guid; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be64 (unsigned long long) ; 
 int /*<<< orphan*/  get_random_bytes (char*,int) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 

void mlx4_set_random_admin_guid(struct mlx4_dev *dev, int entry, int port)
{
	struct mlx4_priv *priv = mlx4_priv(dev);
	__be64 guid;

	/* hw GUID */
	if (entry == 0)
		return;

	get_random_bytes((char *)&guid, sizeof(guid));
	guid &= ~(cpu_to_be64(1ULL << 56));
	guid |= cpu_to_be64(1ULL << 57);
	priv->mfunc.master.vf_admin[entry].vport[port].guid = guid;
}