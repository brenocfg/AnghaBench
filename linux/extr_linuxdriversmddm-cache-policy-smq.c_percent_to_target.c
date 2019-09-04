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
struct smq_policy {int /*<<< orphan*/  cache_size; } ;

/* Variables and functions */
 unsigned int from_cblock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned percent_to_target(struct smq_policy *mq, unsigned p)
{
	return from_cblock(mq->cache_size) * p / 100u;
}