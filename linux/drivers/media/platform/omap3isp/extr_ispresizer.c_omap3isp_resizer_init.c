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
struct isp_res_device {int /*<<< orphan*/  lock; int /*<<< orphan*/  stopping; int /*<<< orphan*/  wait; } ;
struct isp_device {struct isp_res_device isp_res; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int resizer_init_entities (struct isp_res_device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int omap3isp_resizer_init(struct isp_device *isp)
{
	struct isp_res_device *res = &isp->isp_res;

	init_waitqueue_head(&res->wait);
	atomic_set(&res->stopping, 0);
	spin_lock_init(&res->lock);

	return resizer_init_entities(res);
}