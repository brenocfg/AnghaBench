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
struct sclp_req {scalar_t__ status; scalar_t__ sccb; } ;
struct sccb_header {int response_code; } ;

/* Variables and functions */
 scalar_t__ SCLP_REQ_DONE ; 
 int /*<<< orphan*/  sclp_dispatch_evbufs (struct sccb_header*) ; 
 int /*<<< orphan*/  sclp_lock ; 
 int /*<<< orphan*/  sclp_reading_state ; 
 int /*<<< orphan*/  sclp_reading_state_idle ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
sclp_read_cb(struct sclp_req *req, void *data)
{
	unsigned long flags;
	struct sccb_header *sccb;

	sccb = (struct sccb_header *) req->sccb;
	if (req->status == SCLP_REQ_DONE && (sccb->response_code == 0x20 ||
	    sccb->response_code == 0x220))
		sclp_dispatch_evbufs(sccb);
	spin_lock_irqsave(&sclp_lock, flags);
	sclp_reading_state = sclp_reading_state_idle;
	spin_unlock_irqrestore(&sclp_lock, flags);
}