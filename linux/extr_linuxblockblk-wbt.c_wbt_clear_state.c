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
struct request {scalar_t__ wbt_flags; } ;

/* Variables and functions */

__attribute__((used)) static inline void wbt_clear_state(struct request *rq)
{
	rq->wbt_flags = 0;
}