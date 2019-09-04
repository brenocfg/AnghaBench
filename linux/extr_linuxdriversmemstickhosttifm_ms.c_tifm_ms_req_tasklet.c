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
struct tifm_ms {TYPE_1__* req; scalar_t__ eject; struct tifm_dev* dev; } ;
struct tifm_dev {int /*<<< orphan*/  lock; } ;
struct memstick_host {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  error; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETIME ; 
 int memstick_next_req (struct memstick_host*,TYPE_1__**) ; 
 struct tifm_ms* memstick_priv (struct memstick_host*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ tifm_ms_issue_cmd (struct tifm_ms*) ; 

__attribute__((used)) static void tifm_ms_req_tasklet(unsigned long data)
{
	struct memstick_host *msh = (struct memstick_host *)data;
	struct tifm_ms *host = memstick_priv(msh);
	struct tifm_dev *sock = host->dev;
	unsigned long flags;
	int rc;

	spin_lock_irqsave(&sock->lock, flags);
	if (!host->req) {
		if (host->eject) {
			do {
				rc = memstick_next_req(msh, &host->req);
				if (!rc)
					host->req->error = -ETIME;
			} while (!rc);
			spin_unlock_irqrestore(&sock->lock, flags);
			return;
		}

		do {
			rc = memstick_next_req(msh, &host->req);
		} while (!rc && tifm_ms_issue_cmd(host));
	}
	spin_unlock_irqrestore(&sock->lock, flags);
}