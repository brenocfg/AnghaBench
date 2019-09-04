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
struct evdev_client {int dummy; } ;
struct evdev {int /*<<< orphan*/  handle; int /*<<< orphan*/  grab; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  input_release_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct evdev_client* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

__attribute__((used)) static int evdev_ungrab(struct evdev *evdev, struct evdev_client *client)
{
	struct evdev_client *grab = rcu_dereference_protected(evdev->grab,
					lockdep_is_held(&evdev->mutex));

	if (grab != client)
		return  -EINVAL;

	rcu_assign_pointer(evdev->grab, NULL);
	synchronize_rcu();
	input_release_device(&evdev->handle);

	return 0;
}