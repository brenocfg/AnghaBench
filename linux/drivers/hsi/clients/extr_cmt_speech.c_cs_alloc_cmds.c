#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/  sgl; } ;
struct hsi_msg {int /*<<< orphan*/  link; struct cs_hsi_iface* context; int /*<<< orphan*/  channel; TYPE_1__ sgt; } ;
struct cs_hsi_iface {int /*<<< orphan*/  cmdqueue; } ;
struct TYPE_4__ {int /*<<< orphan*/  channel_id_cmd; } ;

/* Variables and functions */
 unsigned int CS_MAX_CMDS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 TYPE_2__ cs_char_data ; 
 int /*<<< orphan*/  cs_free_cmds (struct cs_hsi_iface*) ; 
 struct hsi_msg* hsi_alloc_msg (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hsi_free_msg (struct hsi_msg*) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sg_init_one (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int cs_alloc_cmds(struct cs_hsi_iface *hi)
{
	struct hsi_msg *msg;
	u32 *buf;
	unsigned int i;

	INIT_LIST_HEAD(&hi->cmdqueue);

	for (i = 0; i < CS_MAX_CMDS; i++) {
		msg = hsi_alloc_msg(1, GFP_KERNEL);
		if (!msg)
			goto out;
		buf = kmalloc(sizeof(*buf), GFP_KERNEL);
		if (!buf) {
			hsi_free_msg(msg);
			goto out;
		}
		sg_init_one(msg->sgt.sgl, buf, sizeof(*buf));
		msg->channel = cs_char_data.channel_id_cmd;
		msg->context = hi;
		list_add_tail(&msg->link, &hi->cmdqueue);
	}

	return 0;

out:
	cs_free_cmds(hi);
	return -ENOMEM;
}