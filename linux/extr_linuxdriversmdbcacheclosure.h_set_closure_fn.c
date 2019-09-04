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
struct workqueue_struct {int dummy; } ;
struct closure {struct workqueue_struct* wq; int /*<<< orphan*/ * fn; } ;
typedef  int /*<<< orphan*/  closure_fn ;

/* Variables and functions */
 int /*<<< orphan*/  closure_set_ip (struct closure*) ; 
 int /*<<< orphan*/  smp_mb__before_atomic () ; 

__attribute__((used)) static inline void set_closure_fn(struct closure *cl, closure_fn *fn,
				  struct workqueue_struct *wq)
{
	closure_set_ip(cl);
	cl->fn = fn;
	cl->wq = wq;
	/* between atomic_dec() in closure_put() */
	smp_mb__before_atomic();
}