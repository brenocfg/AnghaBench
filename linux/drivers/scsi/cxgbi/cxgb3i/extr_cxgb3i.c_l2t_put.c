#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct t3cdev {int dummy; } ;
struct cxgbi_sock {int /*<<< orphan*/ * l2t; TYPE_1__* cdev; } ;
struct TYPE_2__ {scalar_t__ lldev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cxgbi_sock_put (struct cxgbi_sock*) ; 
 int /*<<< orphan*/  l2t_release (struct t3cdev*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void l2t_put(struct cxgbi_sock *csk)
{
	struct t3cdev *t3dev = (struct t3cdev *)csk->cdev->lldev;

	if (csk->l2t) {
		l2t_release(t3dev, csk->l2t);
		csk->l2t = NULL;
		cxgbi_sock_put(csk);
	}
}