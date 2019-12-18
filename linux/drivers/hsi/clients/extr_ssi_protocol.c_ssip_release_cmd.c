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
struct ssi_protocol {int /*<<< orphan*/  lock; int /*<<< orphan*/  cmdqueue; } ;
struct hsi_msg {int /*<<< orphan*/  link; TYPE_1__* cl; } ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct ssi_protocol* hsi_client_drvdata (TYPE_1__*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssip_get_cmd (struct hsi_msg*) ; 

__attribute__((used)) static inline void ssip_release_cmd(struct hsi_msg *msg)
{
	struct ssi_protocol *ssi = hsi_client_drvdata(msg->cl);

	dev_dbg(&msg->cl->device, "Release cmd 0x%08x\n", ssip_get_cmd(msg));
	spin_lock_bh(&ssi->lock);
	list_add_tail(&msg->link, &ssi->cmdqueue);
	spin_unlock_bh(&ssi->lock);
}