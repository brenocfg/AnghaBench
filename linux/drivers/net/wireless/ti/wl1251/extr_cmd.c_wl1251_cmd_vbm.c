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
typedef  void* u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {scalar_t__ length; void* identity; int /*<<< orphan*/  pvb_field; void* bitmap_ctrl; } ;
struct wl1251_cmd_vbm_update {int /*<<< orphan*/  len; TYPE_1__ tim; } ;
struct wl1251 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_VBM ; 
 int /*<<< orphan*/  DEBUG_CMD ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PARTIAL_VBM_MAX ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct wl1251_cmd_vbm_update*) ; 
 struct wl1251_cmd_vbm_update* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int wl1251_cmd_send (struct wl1251*,int /*<<< orphan*/ ,struct wl1251_cmd_vbm_update*,int) ; 
 int /*<<< orphan*/  wl1251_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1251_error (char*) ; 
 int /*<<< orphan*/  wl1251_warning (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int wl1251_cmd_vbm(struct wl1251 *wl, u8 identity,
		   void *bitmap, u16 bitmap_len, u8 bitmap_control)
{
	struct wl1251_cmd_vbm_update *vbm;
	int ret;

	wl1251_debug(DEBUG_CMD, "cmd vbm");

	vbm = kzalloc(sizeof(*vbm), GFP_KERNEL);
	if (!vbm) {
		ret = -ENOMEM;
		goto out;
	}

	/* Count and period will be filled by the target */
	vbm->tim.bitmap_ctrl = bitmap_control;
	if (bitmap_len > PARTIAL_VBM_MAX) {
		wl1251_warning("cmd vbm len is %d B, truncating to %d",
			       bitmap_len, PARTIAL_VBM_MAX);
		bitmap_len = PARTIAL_VBM_MAX;
	}
	memcpy(vbm->tim.pvb_field, bitmap, bitmap_len);
	vbm->tim.identity = identity;
	vbm->tim.length = bitmap_len + 3;

	vbm->len = cpu_to_le16(bitmap_len + 5);

	ret = wl1251_cmd_send(wl, CMD_VBM, vbm, sizeof(*vbm));
	if (ret < 0) {
		wl1251_error("VBM command failed");
		goto out;
	}

out:
	kfree(vbm);
	return ret;
}