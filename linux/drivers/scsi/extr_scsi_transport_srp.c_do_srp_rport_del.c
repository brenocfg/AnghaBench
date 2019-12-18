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

/* Variables and functions */
 int /*<<< orphan*/  dev_to_rport (struct device*) ; 
 scalar_t__ scsi_is_srp_rport (struct device*) ; 
 int /*<<< orphan*/  srp_rport_del (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_srp_rport_del(struct device *dev, void *data)
{
	if (scsi_is_srp_rport(dev))
		srp_rport_del(dev_to_rport(dev));
	return 0;
}