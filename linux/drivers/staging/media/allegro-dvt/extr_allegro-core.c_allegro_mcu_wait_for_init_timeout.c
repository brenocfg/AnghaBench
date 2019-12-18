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
struct allegro_dev {int /*<<< orphan*/  init_complete; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  msecs_to_jiffies (unsigned long) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int allegro_mcu_wait_for_init_timeout(struct allegro_dev *dev,
					     unsigned long timeout_ms)
{
	unsigned long tmo;

	tmo = wait_for_completion_timeout(&dev->init_complete,
					  msecs_to_jiffies(timeout_ms));
	if (tmo == 0)
		return -ETIMEDOUT;

	reinit_completion(&dev->init_complete);
	return 0;
}