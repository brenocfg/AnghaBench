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
struct sclp_statechangebuf {int /*<<< orphan*/  sclp_active_facility_mask; scalar_t__ validity_sclp_active_facility_mask; scalar_t__ validity_sclp_send_mask; scalar_t__ validity_sclp_receive_mask; } ;
struct evbuf_header {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  facilities; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  sccb_get_recv_mask (struct sclp_statechangebuf*) ; 
 int /*<<< orphan*/  sccb_get_send_mask (struct sclp_statechangebuf*) ; 
 TYPE_1__ sclp ; 
 int /*<<< orphan*/  sclp_dispatch_state_change () ; 
 int /*<<< orphan*/  sclp_lock ; 
 int /*<<< orphan*/  sclp_receive_mask ; 
 int /*<<< orphan*/  sclp_send_mask ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
sclp_state_change_cb(struct evbuf_header *evbuf)
{
	unsigned long flags;
	struct sclp_statechangebuf *scbuf;

	BUILD_BUG_ON(sizeof(struct sclp_statechangebuf) > PAGE_SIZE);

	scbuf = (struct sclp_statechangebuf *) evbuf;
	spin_lock_irqsave(&sclp_lock, flags);
	if (scbuf->validity_sclp_receive_mask)
		sclp_receive_mask = sccb_get_recv_mask(scbuf);
	if (scbuf->validity_sclp_send_mask)
		sclp_send_mask = sccb_get_send_mask(scbuf);
	spin_unlock_irqrestore(&sclp_lock, flags);
	if (scbuf->validity_sclp_active_facility_mask)
		sclp.facilities = scbuf->sclp_active_facility_mask;
	sclp_dispatch_state_change();
}