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
struct TYPE_2__ {scalar_t__ device; } ;
struct virtio_device {TYPE_1__ id; } ;

/* Variables and functions */
 scalar_t__ VIRTIO_ID_RPROC_SERIAL ; 
 scalar_t__ is_rproc_enabled ; 

__attribute__((used)) static bool is_rproc_serial(const struct virtio_device *vdev)
{
	return is_rproc_enabled && vdev->id.device == VIRTIO_ID_RPROC_SERIAL;
}