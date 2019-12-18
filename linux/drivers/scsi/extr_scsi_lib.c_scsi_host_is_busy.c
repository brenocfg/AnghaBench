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
struct Scsi_Host {scalar_t__ can_queue; scalar_t__ host_self_blocked; int /*<<< orphan*/  host_blocked; int /*<<< orphan*/  host_busy; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool scsi_host_is_busy(struct Scsi_Host *shost)
{
	if (shost->can_queue > 0 &&
	    atomic_read(&shost->host_busy) >= shost->can_queue)
		return true;
	if (atomic_read(&shost->host_blocked) > 0)
		return true;
	if (shost->host_self_blocked)
		return true;
	return false;
}