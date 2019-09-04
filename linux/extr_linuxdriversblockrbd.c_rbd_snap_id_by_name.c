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
typedef  int /*<<< orphan*/  u64 ;
struct rbd_device {int image_format; } ;

/* Variables and functions */
 int /*<<< orphan*/  rbd_v1_snap_id_by_name (struct rbd_device*,char const*) ; 
 int /*<<< orphan*/  rbd_v2_snap_id_by_name (struct rbd_device*,char const*) ; 

__attribute__((used)) static u64 rbd_snap_id_by_name(struct rbd_device *rbd_dev, const char *name)
{
	if (rbd_dev->image_format == 1)
		return rbd_v1_snap_id_by_name(rbd_dev, name);

	return rbd_v2_snap_id_by_name(rbd_dev, name);
}