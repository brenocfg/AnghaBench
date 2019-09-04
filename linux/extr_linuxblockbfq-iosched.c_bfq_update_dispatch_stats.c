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
struct request {int dummy; } ;
struct bfq_queue {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void bfq_update_dispatch_stats(struct request_queue *q,
					     struct request *rq,
					     struct bfq_queue *in_serv_queue,
					     bool idle_timer_disabled) {}