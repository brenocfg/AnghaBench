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
struct smq_policy {int /*<<< orphan*/  cache_alloc; } ;
struct entry {int dummy; } ;
typedef  int /*<<< orphan*/  dm_cblock_t ;

/* Variables and functions */
 int /*<<< orphan*/  get_index (int /*<<< orphan*/ *,struct entry*) ; 
 int /*<<< orphan*/  to_cblock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static dm_cblock_t infer_cblock(struct smq_policy *mq, struct entry *e)
{
	return to_cblock(get_index(&mq->cache_alloc, e));
}