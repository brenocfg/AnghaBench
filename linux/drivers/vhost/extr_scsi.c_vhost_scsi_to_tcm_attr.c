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

/* Variables and functions */
 int TCM_ACA_TAG ; 
 int TCM_HEAD_TAG ; 
 int TCM_ORDERED_TAG ; 
 int TCM_SIMPLE_TAG ; 
#define  VIRTIO_SCSI_S_ACA 131 
#define  VIRTIO_SCSI_S_HEAD 130 
#define  VIRTIO_SCSI_S_ORDERED 129 
#define  VIRTIO_SCSI_S_SIMPLE 128 

__attribute__((used)) static int vhost_scsi_to_tcm_attr(int attr)
{
	switch (attr) {
	case VIRTIO_SCSI_S_SIMPLE:
		return TCM_SIMPLE_TAG;
	case VIRTIO_SCSI_S_ORDERED:
		return TCM_ORDERED_TAG;
	case VIRTIO_SCSI_S_HEAD:
		return TCM_HEAD_TAG;
	case VIRTIO_SCSI_S_ACA:
		return TCM_ACA_TAG;
	default:
		break;
	}
	return TCM_SIMPLE_TAG;
}