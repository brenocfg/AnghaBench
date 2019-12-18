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
struct mddev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __md_stop_writes (struct mddev*) ; 
 int /*<<< orphan*/  mddev_lock_nointr (struct mddev*) ; 
 int /*<<< orphan*/  mddev_unlock (struct mddev*) ; 

void md_stop_writes(struct mddev *mddev)
{
	mddev_lock_nointr(mddev);
	__md_stop_writes(mddev);
	mddev_unlock(mddev);
}