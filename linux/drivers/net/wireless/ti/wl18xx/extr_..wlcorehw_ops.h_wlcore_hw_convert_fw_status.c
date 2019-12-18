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
struct wl_fw_status {int dummy; } ;
struct wl1271 {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* convert_fw_status ) (struct wl1271*,void*,struct wl_fw_status*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  stub1 (struct wl1271*,void*,struct wl_fw_status*) ; 

__attribute__((used)) static inline void
wlcore_hw_convert_fw_status(struct wl1271 *wl, void *raw_fw_status,
			    struct wl_fw_status *fw_status)
{
	BUG_ON(!wl->ops->convert_fw_status);

	wl->ops->convert_fw_status(wl, raw_fw_status, fw_status);
}