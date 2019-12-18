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
struct bch_ratelimit {int /*<<< orphan*/  next; } ;

/* Variables and functions */
 int /*<<< orphan*/  local_clock () ; 

__attribute__((used)) static inline void bch_ratelimit_reset(struct bch_ratelimit *d)
{
	d->next = local_clock();
}