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
struct request_queue {int /*<<< orphan*/  blkcg_pols; } ;
struct blkcg_policy {int /*<<< orphan*/  plid; } ;

/* Variables and functions */
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool blkcg_policy_enabled(struct request_queue *q,
				 const struct blkcg_policy *pol)
{
	return pol && test_bit(pol->plid, q->blkcg_pols);
}