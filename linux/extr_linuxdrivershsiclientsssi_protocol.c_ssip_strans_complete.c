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
struct ssi_protocol {int /*<<< orphan*/  lock; } ;
struct hsi_msg {struct hsi_msg* context; struct hsi_client* cl; } ;
struct hsi_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SENDING ; 
 int /*<<< orphan*/  hsi_async_write (struct hsi_client*,struct hsi_msg*) ; 
 struct ssi_protocol* hsi_client_drvdata (struct hsi_client*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssip_release_cmd (struct hsi_msg*) ; 
 int /*<<< orphan*/  ssip_set_txstate (struct ssi_protocol*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ssip_strans_complete(struct hsi_msg *msg)
{
	struct hsi_client *cl = msg->cl;
	struct ssi_protocol *ssi = hsi_client_drvdata(cl);
	struct hsi_msg *data;

	data = msg->context;
	ssip_release_cmd(msg);
	spin_lock_bh(&ssi->lock);
	ssip_set_txstate(ssi, SENDING);
	spin_unlock_bh(&ssi->lock);
	hsi_async_write(cl, data);
}