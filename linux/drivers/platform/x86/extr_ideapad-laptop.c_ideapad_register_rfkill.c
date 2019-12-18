#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ideapad_private {int /*<<< orphan*/ * rfk; TYPE_2__* adev; TYPE_3__* rfk_priv; TYPE_1__* platform_device; } ;
struct TYPE_8__ {scalar_t__ type; scalar_t__ opcode; int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int dev; struct ideapad_private* priv; } ;
struct TYPE_6__ {int /*<<< orphan*/  handle; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ RFKILL_TYPE_BLUETOOTH ; 
 TYPE_4__* ideapad_rfk_data ; 
 int /*<<< orphan*/  ideapad_rfk_ops ; 
 scalar_t__ no_bt_rfkill ; 
 scalar_t__ read_ec_data (int /*<<< orphan*/ ,scalar_t__,unsigned long*) ; 
 int /*<<< orphan*/  rfkill_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  rfkill_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfkill_init_sw_state (int /*<<< orphan*/ ,unsigned long) ; 
 int rfkill_register (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_ec_cmd (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static int ideapad_register_rfkill(struct ideapad_private *priv, int dev)
{
	int ret;
	unsigned long sw_blocked;

	if (no_bt_rfkill &&
	    (ideapad_rfk_data[dev].type == RFKILL_TYPE_BLUETOOTH)) {
		/* Force to enable bluetooth when no_bt_rfkill=1 */
		write_ec_cmd(priv->adev->handle,
			     ideapad_rfk_data[dev].opcode, 1);
		return 0;
	}
	priv->rfk_priv[dev].dev = dev;
	priv->rfk_priv[dev].priv = priv;

	priv->rfk[dev] = rfkill_alloc(ideapad_rfk_data[dev].name,
				      &priv->platform_device->dev,
				      ideapad_rfk_data[dev].type,
				      &ideapad_rfk_ops,
				      &priv->rfk_priv[dev]);
	if (!priv->rfk[dev])
		return -ENOMEM;

	if (read_ec_data(priv->adev->handle, ideapad_rfk_data[dev].opcode-1,
			 &sw_blocked)) {
		rfkill_init_sw_state(priv->rfk[dev], 0);
	} else {
		sw_blocked = !sw_blocked;
		rfkill_init_sw_state(priv->rfk[dev], sw_blocked);
	}

	ret = rfkill_register(priv->rfk[dev]);
	if (ret) {
		rfkill_destroy(priv->rfk[dev]);
		return ret;
	}
	return 0;
}