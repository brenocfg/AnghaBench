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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct tb_regs_switch_header {int route_hi; int member_0; int route_lo; int member_1; int enabled; int member_2; } ;
struct tb_cfg_result {int err; } ;
struct tb {int /*<<< orphan*/  ctl; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  TB_CFG_DEFAULT_TIMEOUT ; 
 struct tb_cfg_result tb_cfg_reset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int tb_cfg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  tb_dbg (struct tb*,char*,int) ; 

int tb_switch_reset(struct tb *tb, u64 route)
{
	struct tb_cfg_result res;
	struct tb_regs_switch_header header = {
		header.route_hi = route >> 32,
		header.route_lo = route,
		header.enabled = true,
	};
	tb_dbg(tb, "resetting switch at %llx\n", route);
	res.err = tb_cfg_write(tb->ctl, ((u32 *) &header) + 2, route,
			0, 2, 2, 2);
	if (res.err)
		return res.err;
	res = tb_cfg_reset(tb->ctl, route, TB_CFG_DEFAULT_TIMEOUT);
	if (res.err > 0)
		return -EIO;
	return res.err;
}