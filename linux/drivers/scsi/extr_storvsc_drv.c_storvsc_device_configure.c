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
struct scsi_device {int no_write_same; int /*<<< orphan*/  scsi_level; int /*<<< orphan*/  vendor; int /*<<< orphan*/  request_queue; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  SCSI_SPC_3 ; 
 int VMSTOR_PROTO_VERSION_WIN10 ; 
#define  VMSTOR_PROTO_VERSION_WIN8 129 
#define  VMSTOR_PROTO_VERSION_WIN8_1 128 
 int /*<<< orphan*/  blk_queue_rq_timeout (int /*<<< orphan*/ ,int) ; 
 int storvsc_timeout ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char*,int) ; 
 int vmstor_proto_version ; 

__attribute__((used)) static int storvsc_device_configure(struct scsi_device *sdevice)
{
	blk_queue_rq_timeout(sdevice->request_queue, (storvsc_timeout * HZ));

	sdevice->no_write_same = 1;

	/*
	 * If the host is WIN8 or WIN8 R2, claim conformance to SPC-3
	 * if the device is a MSFT virtual device.  If the host is
	 * WIN10 or newer, allow write_same.
	 */
	if (!strncmp(sdevice->vendor, "Msft", 4)) {
		switch (vmstor_proto_version) {
		case VMSTOR_PROTO_VERSION_WIN8:
		case VMSTOR_PROTO_VERSION_WIN8_1:
			sdevice->scsi_level = SCSI_SPC_3;
			break;
		}

		if (vmstor_proto_version >= VMSTOR_PROTO_VERSION_WIN10)
			sdevice->no_write_same = 0;
	}

	return 0;
}