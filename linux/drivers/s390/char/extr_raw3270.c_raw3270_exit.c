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

/* Variables and functions */
 int /*<<< orphan*/  ccw_driver_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  class3270 ; 
 int /*<<< orphan*/  class_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw3270_ccw_driver ; 

__attribute__((used)) static void
raw3270_exit(void)
{
	ccw_driver_unregister(&raw3270_ccw_driver);
	class_destroy(class3270);
}