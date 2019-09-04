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
struct sg_io_v4 {scalar_t__ protocol; scalar_t__ subprotocol; } ;

/* Variables and functions */
 scalar_t__ BSG_PROTOCOL_SCSI ; 
 scalar_t__ BSG_SUB_PROTOCOL_SCSI_CMD ; 
 int EINVAL ; 

__attribute__((used)) static int bsg_scsi_check_proto(struct sg_io_v4 *hdr)
{
	if (hdr->protocol != BSG_PROTOCOL_SCSI  ||
	    hdr->subprotocol != BSG_SUB_PROTOCOL_SCSI_CMD)
		return -EINVAL;
	return 0;
}