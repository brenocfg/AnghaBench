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
struct virtio_iommu_req_tail {int status; } ;

/* Variables and functions */

__attribute__((used)) static void viommu_set_req_status(void *buf, size_t len, int status)
{
	struct virtio_iommu_req_tail *tail = buf + len - sizeof(*tail);

	tail->status = status;
}