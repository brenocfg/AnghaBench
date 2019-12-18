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
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UIO_MAX_DEVICES ; 
 int /*<<< orphan*/  cdev_del (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uio_cdev ; 
 int /*<<< orphan*/  uio_major ; 
 int /*<<< orphan*/  unregister_chrdev_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void uio_major_cleanup(void)
{
	unregister_chrdev_region(MKDEV(uio_major, 0), UIO_MAX_DEVICES);
	cdev_del(uio_cdev);
}