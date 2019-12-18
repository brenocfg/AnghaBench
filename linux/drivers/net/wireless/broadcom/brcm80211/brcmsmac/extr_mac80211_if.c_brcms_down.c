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
typedef  scalar_t__ uint ;
struct brcms_info {int /*<<< orphan*/  lock; int /*<<< orphan*/  callbacks; int /*<<< orphan*/  wlc; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPINWAIT (int,int) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ brcms_c_down (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void brcms_down(struct brcms_info *wl)
{
	uint callbacks, ret_val = 0;

	/* call common down function */
	ret_val = brcms_c_down(wl->wlc);
	callbacks = atomic_read(&wl->callbacks) - ret_val;

	/* wait for down callbacks to complete */
	spin_unlock_bh(&wl->lock);

	/* For HIGH_only driver, it's important to actually schedule other work,
	 * not just spin wait since everything runs at schedule level
	 */
	SPINWAIT((atomic_read(&wl->callbacks) > callbacks), 100 * 1000);

	spin_lock_bh(&wl->lock);
}