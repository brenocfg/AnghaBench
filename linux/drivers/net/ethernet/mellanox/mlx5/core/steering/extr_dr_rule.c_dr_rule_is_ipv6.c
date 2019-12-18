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
struct TYPE_4__ {int ip_version; scalar_t__ ethertype; } ;
struct TYPE_3__ {int ip_version; scalar_t__ ethertype; } ;
struct mlx5dr_match_param {TYPE_2__ inner; TYPE_1__ outer; } ;

/* Variables and functions */
 scalar_t__ ETH_P_IPV6 ; 

__attribute__((used)) static bool dr_rule_is_ipv6(struct mlx5dr_match_param *param)
{
	return (param->outer.ip_version == 6 ||
		param->inner.ip_version == 6 ||
		param->outer.ethertype == ETH_P_IPV6 ||
		param->inner.ethertype == ETH_P_IPV6);
}