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
struct be_queue_info {int /*<<< orphan*/  len; int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int /*<<< orphan*/  index_inc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void queue_head_inc(struct be_queue_info *q)
{
	index_inc(&q->head, q->len);
}