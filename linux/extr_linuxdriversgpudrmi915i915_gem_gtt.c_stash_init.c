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
struct pagestash {int /*<<< orphan*/  lock; int /*<<< orphan*/  pvec; } ;

/* Variables and functions */
 int /*<<< orphan*/  pagevec_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stash_init(struct pagestash *stash)
{
	pagevec_init(&stash->pvec);
	spin_lock_init(&stash->lock);
}