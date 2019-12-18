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
typedef  int u32 ;
struct wl1271 {int dummy; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_TESTMODE ; 
 int EINVAL ; 
#define  PLT_CHIP_AWAKE 131 
#define  PLT_FEM_DETECT 130 
#define  PLT_OFF 129 
#define  PLT_ON 128 
 size_t WL1271_TM_ATTR_PLT_MODE ; 
 int nla_get_u32 (struct nlattr*) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*) ; 
 int wl1271_plt_start (struct wl1271*,int) ; 
 int wl1271_plt_stop (struct wl1271*) ; 
 int wl1271_tm_detect_fem (struct wl1271*,struct nlattr**) ; 

__attribute__((used)) static int wl1271_tm_cmd_set_plt_mode(struct wl1271 *wl, struct nlattr *tb[])
{
	u32 val;
	int ret;

	wl1271_debug(DEBUG_TESTMODE, "testmode cmd set plt mode");

	if (!tb[WL1271_TM_ATTR_PLT_MODE])
		return -EINVAL;

	val = nla_get_u32(tb[WL1271_TM_ATTR_PLT_MODE]);

	switch (val) {
	case PLT_OFF:
		ret = wl1271_plt_stop(wl);
		break;
	case PLT_ON:
	case PLT_CHIP_AWAKE:
		ret = wl1271_plt_start(wl, val);
		break;
	case PLT_FEM_DETECT:
		ret = wl1271_tm_detect_fem(wl, tb);
		break;
	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}