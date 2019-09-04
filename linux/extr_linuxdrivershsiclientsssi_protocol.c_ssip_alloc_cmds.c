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
typedef  int /*<<< orphan*/  u32 ;
struct ssi_protocol {int /*<<< orphan*/  cmdqueue; int /*<<< orphan*/  channel_id_cmd; } ;
struct TYPE_2__ {int /*<<< orphan*/  sgl; } ;
struct hsi_msg {int /*<<< orphan*/  link; int /*<<< orphan*/  channel; TYPE_1__ sgt; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int SSIP_MAX_CMDS ; 
 struct hsi_msg* hsi_alloc_msg (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hsi_free_msg (struct hsi_msg*) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sg_init_one (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ssip_free_cmds (struct ssi_protocol*) ; 

__attribute__((used)) static int ssip_alloc_cmds(struct ssi_protocol *ssi)
{
	struct hsi_msg *msg;
	u32 *buf;
	unsigned int i;

	for (i = 0; i < SSIP_MAX_CMDS; i++) {
		msg = hsi_alloc_msg(1, GFP_KERNEL);
		if (!msg)
			goto out;
		buf = kmalloc(sizeof(*buf), GFP_KERNEL);
		if (!buf) {
			hsi_free_msg(msg);
			goto out;
		}
		sg_init_one(msg->sgt.sgl, buf, sizeof(*buf));
		msg->channel = ssi->channel_id_cmd;
		list_add_tail(&msg->link, &ssi->cmdqueue);
	}

	return 0;
out:
	ssip_free_cmds(ssi);

	return -ENOMEM;
}