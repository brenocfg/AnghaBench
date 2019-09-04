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
struct ib_pd {int dummy; } ;
struct rxe_pd {struct ib_pd ibpd; } ;
struct rxe_dev {int /*<<< orphan*/  pd_pool; } ;
struct ib_udata {int dummy; } ;
struct ib_ucontext {int dummy; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct ib_pd* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct rxe_pd* rxe_alloc (int /*<<< orphan*/ *) ; 
 struct rxe_dev* to_rdev (struct ib_device*) ; 

__attribute__((used)) static struct ib_pd *rxe_alloc_pd(struct ib_device *dev,
				  struct ib_ucontext *context,
				  struct ib_udata *udata)
{
	struct rxe_dev *rxe = to_rdev(dev);
	struct rxe_pd *pd;

	pd = rxe_alloc(&rxe->pd_pool);
	return pd ? &pd->ibpd : ERR_PTR(-ENOMEM);
}