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
struct device {int dummy; } ;
struct Scsi_Host {int /*<<< orphan*/  shost_gendev; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 struct srp_rport* dev_to_rport (struct device*) ; 
 scalar_t__ device_for_each_child (int /*<<< orphan*/ *,struct device**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_child_rport ; 

__attribute__((used)) static inline struct srp_rport *shost_to_rport(struct Scsi_Host *shost)
{
	struct device *child = NULL;

	WARN_ON_ONCE(device_for_each_child(&shost->shost_gendev, &child,
					   find_child_rport) < 0);
	return child ? dev_to_rport(child) : NULL;
}