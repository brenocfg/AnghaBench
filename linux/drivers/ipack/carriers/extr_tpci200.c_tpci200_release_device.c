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
struct ipack_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ipack_device*) ; 

__attribute__((used)) static void tpci200_release_device(struct ipack_device *dev)
{
	kfree(dev);
}