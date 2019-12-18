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
struct srp_rport {int dummy; } ;
struct device {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 struct srp_rport* dev_to_rport (struct device*) ; 
 int /*<<< orphan*/  kfree (struct srp_rport*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void srp_rport_release(struct device *dev)
{
	struct srp_rport *rport = dev_to_rport(dev);

	put_device(dev->parent);
	kfree(rport);
}