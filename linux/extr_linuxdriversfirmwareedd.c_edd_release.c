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
struct kobject {int dummy; } ;
struct edd_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct edd_device*) ; 
 struct edd_device* to_edd_device (struct kobject*) ; 

__attribute__((used)) static void edd_release(struct kobject * kobj)
{
	struct edd_device * dev = to_edd_device(kobj);
	kfree(dev);
}