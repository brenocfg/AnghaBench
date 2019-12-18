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
struct vhost_scsi_evt {int dummy; } ;
struct vhost_scsi {int /*<<< orphan*/  vs_events_nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct vhost_scsi_evt*) ; 

__attribute__((used)) static void vhost_scsi_free_evt(struct vhost_scsi *vs, struct vhost_scsi_evt *evt)
{
	vs->vs_events_nr--;
	kfree(evt);
}