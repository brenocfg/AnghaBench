#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct Scsi_Host {TYPE_1__* hostt; } ;
struct TYPE_2__ {int can_queue; } ;

/* Variables and functions */
 scalar_t__ IS_A_TT () ; 
 scalar_t__ in_interrupt () ; 
 int /*<<< orphan*/  scsi_falcon_intr ; 
 scalar_t__ stdma_is_locked_by (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdma_lock (int /*<<< orphan*/ ,struct Scsi_Host*) ; 
 int stdma_try_lock (int /*<<< orphan*/ ,struct Scsi_Host*) ; 

__attribute__((used)) static int falcon_get_lock(struct Scsi_Host *instance)
{
	if (IS_A_TT())
		return 1;

	if (stdma_is_locked_by(scsi_falcon_intr) &&
	    instance->hostt->can_queue > 1)
		return 1;

	if (in_interrupt())
		return stdma_try_lock(scsi_falcon_intr, instance);

	stdma_lock(scsi_falcon_intr, instance);
	return 1;
}