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
typedef  int u32 ;
struct omap_sham_dev {int dummy; } ;

/* Variables and functions */
 unsigned long DEFAULT_TIMEOUT_INTERVAL ; 
 int ETIMEDOUT ; 
 unsigned long jiffies ; 
 int omap_sham_read (struct omap_sham_dev*,int) ; 
 scalar_t__ time_is_before_jiffies (unsigned long) ; 

__attribute__((used)) static inline int omap_sham_wait(struct omap_sham_dev *dd, u32 offset, u32 bit)
{
	unsigned long timeout = jiffies + DEFAULT_TIMEOUT_INTERVAL;

	while (!(omap_sham_read(dd, offset) & bit)) {
		if (time_is_before_jiffies(timeout))
			return -ETIMEDOUT;
	}

	return 0;
}