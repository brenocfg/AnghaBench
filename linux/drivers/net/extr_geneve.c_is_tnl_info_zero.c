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
struct TYPE_2__ {int /*<<< orphan*/  u; scalar_t__ tp_src; scalar_t__ label; scalar_t__ ttl; scalar_t__ tos; scalar_t__ tun_flags; scalar_t__ tun_id; } ;
struct ip_tunnel_info {TYPE_1__ key; } ;

/* Variables and functions */
 scalar_t__ memchr_inv (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool is_tnl_info_zero(const struct ip_tunnel_info *info)
{
	return !(info->key.tun_id || info->key.tun_flags || info->key.tos ||
		 info->key.ttl || info->key.label || info->key.tp_src ||
		 memchr_inv(&info->key.u, 0, sizeof(info->key.u)));
}