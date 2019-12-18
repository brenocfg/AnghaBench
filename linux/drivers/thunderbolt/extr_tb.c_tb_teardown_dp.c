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
struct tb_port {int dummy; } ;
struct tb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TB_TUNNEL_DP ; 
 int /*<<< orphan*/  tb_free_tunnel (struct tb*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct tb_port*) ; 

__attribute__((used)) static void tb_teardown_dp(struct tb *tb, struct tb_port *out)
{
	tb_free_tunnel(tb, TB_TUNNEL_DP, NULL, out);
}