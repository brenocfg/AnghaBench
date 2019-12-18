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
struct ip_tunnel_info {int options_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct ip_tunnel_info* kmemdup (struct ip_tunnel_info const*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ip_tunnel_info *dup_tun_info(const struct ip_tunnel_info *tun_info)
{
	size_t tun_size = sizeof(*tun_info) + tun_info->options_len;

	return kmemdup(tun_info, tun_size, GFP_KERNEL);
}