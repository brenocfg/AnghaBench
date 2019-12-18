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
 int /*<<< orphan*/  IBM_FS3270_MAJOR ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __unregister_chrdev (int /*<<< orphan*/ ,int,int,char*) ; 
 int /*<<< orphan*/  class3270 ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fs3270_destroy_cb(int minor)
{
	device_destroy(class3270, MKDEV(IBM_FS3270_MAJOR, minor));
	__unregister_chrdev(IBM_FS3270_MAJOR, minor, 1, "tub");
}