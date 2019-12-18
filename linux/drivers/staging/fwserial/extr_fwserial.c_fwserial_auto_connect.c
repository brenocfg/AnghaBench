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
struct work_struct {int dummy; } ;
struct fwtty_peer {scalar_t__ connect_retries; int /*<<< orphan*/  connect; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONNECT_RETRY_DELAY ; 
 int EAGAIN ; 
 scalar_t__ MAX_CONNECT_RETRIES ; 
 int /*<<< orphan*/  connect ; 
 int fwserial_connect_peer (struct fwtty_peer*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_delayed_work (struct work_struct*) ; 
 struct fwtty_peer* to_peer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fwserial_auto_connect(struct work_struct *work)
{
	struct fwtty_peer *peer = to_peer(to_delayed_work(work), connect);
	int err;

	err = fwserial_connect_peer(peer);
	if (err == -EAGAIN && ++peer->connect_retries < MAX_CONNECT_RETRIES)
		schedule_delayed_work(&peer->connect, CONNECT_RETRY_DELAY);
}