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
struct zfcp_reqlist {int /*<<< orphan*/  lock; } ;
struct zfcp_fsf_req {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 struct zfcp_fsf_req* _zfcp_reqlist_find (struct zfcp_reqlist*,unsigned long) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline struct zfcp_fsf_req *
zfcp_reqlist_find_rm(struct zfcp_reqlist *rl, unsigned long req_id)
{
	unsigned long flags;
	struct zfcp_fsf_req *req;

	spin_lock_irqsave(&rl->lock, flags);
	req = _zfcp_reqlist_find(rl, req_id);
	if (req)
		list_del(&req->list);
	spin_unlock_irqrestore(&rl->lock, flags);

	return req;
}