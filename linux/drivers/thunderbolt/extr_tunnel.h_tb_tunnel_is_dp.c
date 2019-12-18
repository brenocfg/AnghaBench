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
struct tb_tunnel {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ TB_TUNNEL_DP ; 

__attribute__((used)) static inline bool tb_tunnel_is_dp(const struct tb_tunnel *tunnel)
{
	return tunnel->type == TB_TUNNEL_DP;
}