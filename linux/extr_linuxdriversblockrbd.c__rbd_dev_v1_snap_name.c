#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_4__ {char* snap_names; TYPE_1__* snapc; } ;
struct rbd_device {TYPE_2__ header; } ;
struct TYPE_3__ {scalar_t__ num_snaps; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 char const* kstrdup (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rbd_assert (int) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static const char *_rbd_dev_v1_snap_name(struct rbd_device *rbd_dev, u32 which)
{
	const char *snap_name;

	rbd_assert(which < rbd_dev->header.snapc->num_snaps);

	/* Skip over names until we find the one we are looking for */

	snap_name = rbd_dev->header.snap_names;
	while (which--)
		snap_name += strlen(snap_name) + 1;

	return kstrdup(snap_name, GFP_KERNEL);
}