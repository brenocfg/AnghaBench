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
struct ccw_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dasd_fba_discipline ; 
 int dasd_generic_set_online (struct ccw_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
dasd_fba_set_online(struct ccw_device *cdev)
{
	return dasd_generic_set_online(cdev, &dasd_fba_discipline);
}