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
struct v4l2_async_notifier {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* complete ) (struct v4l2_async_notifier*) ;} ;

/* Variables and functions */
 int stub1 (struct v4l2_async_notifier*) ; 

__attribute__((used)) static int v4l2_async_notifier_call_complete(struct v4l2_async_notifier *n)
{
	if (!n->ops || !n->ops->complete)
		return 0;

	return n->ops->complete(n);
}