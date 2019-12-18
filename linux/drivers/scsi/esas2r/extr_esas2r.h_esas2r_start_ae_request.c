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
struct esas2r_request {int dummy; } ;
struct esas2r_adapter {int /*<<< orphan*/  queue_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  esas2r_build_ae_req (struct esas2r_adapter*,struct esas2r_request*) ; 
 int /*<<< orphan*/  esas2r_start_vda_request (struct esas2r_adapter*,struct esas2r_request*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void esas2r_start_ae_request(struct esas2r_adapter *a,
					   struct esas2r_request *rq)
{
	unsigned long flags;

	esas2r_build_ae_req(a, rq);

	spin_lock_irqsave(&a->queue_lock, flags);
	esas2r_start_vda_request(a, rq);
	spin_unlock_irqrestore(&a->queue_lock, flags);
}