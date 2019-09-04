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
typedef  int /*<<< orphan*/  u32 ;
struct dw_i2c_dev {int flags; } ;

/* Variables and functions */
 int MODEL_CHERRYTRAIL ; 
 int /*<<< orphan*/  PUNIT_SEMAPHORE ; 
 int /*<<< orphan*/  PUNIT_SEMAPHORE_CHT ; 

__attribute__((used)) static u32 get_sem_addr(struct dw_i2c_dev *dev)
{
	if (dev->flags & MODEL_CHERRYTRAIL)
		return PUNIT_SEMAPHORE_CHT;
	else
		return PUNIT_SEMAPHORE;
}