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
struct TYPE_2__ {size_t exttype; size_t devtype; } ;
struct wiimote_data {TYPE_1__ state; } ;
struct wiimod_ops {int /*<<< orphan*/  (* in_ir ) (struct wiimote_data*,size_t const*,int,unsigned int) ;} ;
typedef  size_t __u8 ;

/* Variables and functions */
 size_t const WIIMOD_NULL ; 
 int /*<<< orphan*/  stub1 (struct wiimote_data*,size_t const*,int,unsigned int) ; 
 int /*<<< orphan*/  stub2 (struct wiimote_data*,size_t const*,int,unsigned int) ; 
 struct wiimod_ops** wiimod_ext_table ; 
 struct wiimod_ops** wiimod_table ; 
 size_t** wiimote_devtype_mods ; 

__attribute__((used)) static void handler_ir(struct wiimote_data *wdata, const __u8 *payload,
		       bool packed, unsigned int id)
{
	const __u8 *iter, *mods;
	const struct wiimod_ops *ops;

	ops = wiimod_ext_table[wdata->state.exttype];
	if (ops->in_ir) {
		ops->in_ir(wdata, payload, packed, id);
		return;
	}

	mods = wiimote_devtype_mods[wdata->state.devtype];
	for (iter = mods; *iter != WIIMOD_NULL; ++iter) {
		ops = wiimod_table[*iter];
		if (ops->in_ir) {
			ops->in_ir(wdata, payload, packed, id);
			break;
		}
	}
}