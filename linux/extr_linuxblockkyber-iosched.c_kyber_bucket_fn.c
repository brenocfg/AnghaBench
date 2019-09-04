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
struct request {int /*<<< orphan*/  cmd_flags; } ;

/* Variables and functions */
 int kyber_sched_domain (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kyber_bucket_fn(const struct request *rq)
{
	return kyber_sched_domain(rq->cmd_flags);
}