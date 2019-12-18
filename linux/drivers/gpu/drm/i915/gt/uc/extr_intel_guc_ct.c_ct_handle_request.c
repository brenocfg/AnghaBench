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
typedef  int u32 ;
struct intel_guc_ct {int /*<<< orphan*/  worker; int /*<<< orphan*/  lock; int /*<<< orphan*/  incoming_requests; } ;
struct ct_incoming_request {int /*<<< orphan*/  link; int /*<<< orphan*/  msg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int,int const*) ; 
 int /*<<< orphan*/  GEM_BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int ct_header_get_len (int) ; 
 int /*<<< orphan*/  ct_header_is_response (int) ; 
 struct ct_incoming_request* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int const*,int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  system_unbound_wq ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ct_handle_request(struct intel_guc_ct *ct, const u32 *msg)
{
	u32 header = msg[0];
	u32 len = ct_header_get_len(header);
	u32 msglen = len + 1; /* total message length including header */
	struct ct_incoming_request *request;
	unsigned long flags;

	GEM_BUG_ON(ct_header_is_response(header));

	request = kmalloc(sizeof(*request) + 4 * msglen, GFP_ATOMIC);
	if (unlikely(!request)) {
		DRM_ERROR("CT: dropping request %*ph\n", 4 * msglen, msg);
		return 0; /* XXX: -ENOMEM ? */
	}
	memcpy(request->msg, msg, 4 * msglen);

	spin_lock_irqsave(&ct->lock, flags);
	list_add_tail(&request->link, &ct->incoming_requests);
	spin_unlock_irqrestore(&ct->lock, flags);

	queue_work(system_unbound_wq, &ct->worker);
	return 0;
}