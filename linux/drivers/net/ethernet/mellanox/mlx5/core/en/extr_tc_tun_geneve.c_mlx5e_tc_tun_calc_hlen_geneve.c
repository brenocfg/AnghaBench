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
struct udphdr {int dummy; } ;
struct mlx5e_encap_entry {TYPE_1__* tun_info; } ;
struct genevehdr {int dummy; } ;
struct TYPE_2__ {int options_len; } ;

/* Variables and functions */

__attribute__((used)) static int mlx5e_tc_tun_calc_hlen_geneve(struct mlx5e_encap_entry *e)
{
	return sizeof(struct udphdr) +
	       sizeof(struct genevehdr) +
	       e->tun_info->options_len;
}