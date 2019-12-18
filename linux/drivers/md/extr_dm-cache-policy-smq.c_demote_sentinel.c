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
struct smq_policy {int /*<<< orphan*/  current_demote_sentinels; int /*<<< orphan*/  demote_sentinel_alloc; } ;
struct entry {int dummy; } ;

/* Variables and functions */
 struct entry* get_sentinel (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct entry *demote_sentinel(struct smq_policy *mq, unsigned level)
{
	return get_sentinel(&mq->demote_sentinel_alloc, level, mq->current_demote_sentinels);
}