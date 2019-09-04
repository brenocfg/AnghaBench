#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct hsi_msg {scalar_t__ ttype; struct cs_hsi_iface* context; } ;
struct cs_hsi_iface {scalar_t__ iface_state; int control_state; int /*<<< orphan*/  lock; TYPE_2__* cl; } ;
struct TYPE_6__ {TYPE_1__* cl; } ;
struct TYPE_5__ {int /*<<< orphan*/  device; } ;
struct TYPE_4__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 scalar_t__ CS_STATE_CLOSED ; 
 scalar_t__ HSI_MSG_READ ; 
 scalar_t__ HSI_MSG_WRITE ; 
 int SSI_CHANNEL_STATE_POLL ; 
 int SSI_CHANNEL_STATE_READING ; 
 int SSI_CHANNEL_STATE_WRITING ; 
 TYPE_3__ cs_char_data ; 
 int /*<<< orphan*/  cs_release_cmd (struct hsi_msg*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cs_cmd_destructor(struct hsi_msg *msg)
{
	struct cs_hsi_iface *hi = msg->context;

	spin_lock(&hi->lock);

	dev_dbg(&cs_char_data.cl->device, "control cmd destructor\n");

	if (hi->iface_state != CS_STATE_CLOSED)
		dev_err(&hi->cl->device, "Cmd flushed while driver active\n");

	if (msg->ttype == HSI_MSG_READ)
		hi->control_state &=
			~(SSI_CHANNEL_STATE_POLL | SSI_CHANNEL_STATE_READING);
	else if (msg->ttype == HSI_MSG_WRITE &&
			hi->control_state & SSI_CHANNEL_STATE_WRITING)
		hi->control_state &= ~SSI_CHANNEL_STATE_WRITING;

	cs_release_cmd(msg);

	spin_unlock(&hi->lock);
}