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
struct request_queue {int dummy; } ;
struct bfq_queue {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void bfq_update_insert_stats(struct request_queue *q,
					   struct bfq_queue *bfqq,
					   bool idle_timer_disabled,
					   unsigned int cmd_flags) {}