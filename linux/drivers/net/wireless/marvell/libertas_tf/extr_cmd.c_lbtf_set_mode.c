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
struct lbtf_private {int dummy; } ;
struct TYPE_2__ {void* size; } ;
struct cmd_ds_set_mode {TYPE_1__ hdr; void* mode; } ;
typedef  enum lbtf_mode { ____Placeholder_lbtf_mode } lbtf_mode ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_802_11_SET_MODE ; 
 int /*<<< orphan*/  LBTF_DEB_WEXT ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  lbtf_cmd_async (struct lbtf_private*,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  lbtf_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbtf_deb_leave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbtf_deb_wext (char*,int) ; 

void lbtf_set_mode(struct lbtf_private *priv, enum lbtf_mode mode)
{
	struct cmd_ds_set_mode cmd;
	lbtf_deb_enter(LBTF_DEB_WEXT);

	cmd.hdr.size = cpu_to_le16(sizeof(cmd));
	cmd.mode = cpu_to_le16(mode);
	lbtf_deb_wext("Switching to mode: 0x%x\n", mode);
	lbtf_cmd_async(priv, CMD_802_11_SET_MODE, &cmd.hdr, sizeof(cmd));

	lbtf_deb_leave(LBTF_DEB_WEXT);
}