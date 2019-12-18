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
struct device {int dummy; } ;
struct cosm_device {int dummy; } ;

/* Variables and functions */
 struct cosm_device* dev_to_cosm (struct device*) ; 
 int /*<<< orphan*/  kfree (struct cosm_device*) ; 

__attribute__((used)) static inline void cosm_release_dev(struct device *d)
{
	struct cosm_device *cdev = dev_to_cosm(d);

	kfree(cdev);
}