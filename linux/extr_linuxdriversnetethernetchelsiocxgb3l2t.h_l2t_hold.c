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
struct l2t_entry {int /*<<< orphan*/  refcnt; } ;
struct l2t_data {int /*<<< orphan*/  nfree; } ;

/* Variables and functions */
 int atomic_add_return (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void l2t_hold(struct l2t_data *d, struct l2t_entry *e)
{
	if (d && atomic_add_return(1, &e->refcnt) == 1)	/* 0 -> 1 transition */
		atomic_dec(&d->nfree);
}