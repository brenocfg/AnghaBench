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
struct ipoib_neigh {int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipoib_neigh_dtor (struct ipoib_neigh*) ; 

__attribute__((used)) static inline void ipoib_neigh_put(struct ipoib_neigh *neigh)
{
	if (atomic_dec_and_test(&neigh->refcnt))
		ipoib_neigh_dtor(neigh);
}