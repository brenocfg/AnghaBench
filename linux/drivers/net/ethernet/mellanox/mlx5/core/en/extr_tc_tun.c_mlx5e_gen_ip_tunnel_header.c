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
struct mlx5e_encap_entry {TYPE_1__* tunnel; } ;
typedef  int /*<<< orphan*/  __u8 ;
struct TYPE_2__ {int (* generate_ip_tun_hdr ) (char*,int /*<<< orphan*/ *,struct mlx5e_encap_entry*) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int stub1 (char*,int /*<<< orphan*/ *,struct mlx5e_encap_entry*) ; 

__attribute__((used)) static int mlx5e_gen_ip_tunnel_header(char buf[], __u8 *ip_proto,
				      struct mlx5e_encap_entry *e)
{
	if (!e->tunnel) {
		pr_warn("mlx5: Cannot generate tunnel header for this tunnel\n");
		return -EOPNOTSUPP;
	}

	return e->tunnel->generate_ip_tun_hdr(buf, ip_proto, e);
}