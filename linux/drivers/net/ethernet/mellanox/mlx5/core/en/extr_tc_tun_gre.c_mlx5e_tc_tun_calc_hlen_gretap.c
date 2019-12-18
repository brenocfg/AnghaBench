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
struct mlx5e_encap_entry {TYPE_2__* tun_info; } ;
struct TYPE_3__ {int /*<<< orphan*/  tun_flags; } ;
struct TYPE_4__ {TYPE_1__ key; } ;

/* Variables and functions */
 int gre_calc_hlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx5e_tc_tun_calc_hlen_gretap(struct mlx5e_encap_entry *e)
{
	return gre_calc_hlen(e->tun_info->key.tun_flags);
}