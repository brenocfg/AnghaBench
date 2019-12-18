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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct tb_ctl {int dummy; } ;
struct tb_cfg_result {int err; int response_port; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  TB_CFG_DEFAULT_TIMEOUT ; 
 int /*<<< orphan*/  TB_CFG_SWITCH ; 
 struct tb_cfg_result tb_cfg_read_raw (struct tb_ctl*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int tb_cfg_get_upstream_port(struct tb_ctl *ctl, u64 route)
{
	u32 dummy;
	struct tb_cfg_result res = tb_cfg_read_raw(ctl, &dummy, route, 0,
						   TB_CFG_SWITCH, 0, 1,
						   TB_CFG_DEFAULT_TIMEOUT);
	if (res.err == 1)
		return -EIO;
	if (res.err)
		return res.err;
	return res.response_port;
}