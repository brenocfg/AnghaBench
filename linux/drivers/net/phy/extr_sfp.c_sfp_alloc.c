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
struct sfp {int /*<<< orphan*/  timeout; int /*<<< orphan*/  poll; int /*<<< orphan*/  st_mutex; int /*<<< orphan*/  sm_mutex; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct sfp* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct sfp* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sfp_poll ; 
 int /*<<< orphan*/  sfp_timeout ; 

__attribute__((used)) static struct sfp *sfp_alloc(struct device *dev)
{
	struct sfp *sfp;

	sfp = kzalloc(sizeof(*sfp), GFP_KERNEL);
	if (!sfp)
		return ERR_PTR(-ENOMEM);

	sfp->dev = dev;

	mutex_init(&sfp->sm_mutex);
	mutex_init(&sfp->st_mutex);
	INIT_DELAYED_WORK(&sfp->poll, sfp_poll);
	INIT_DELAYED_WORK(&sfp->timeout, sfp_timeout);

	return sfp;
}