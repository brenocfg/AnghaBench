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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct viosrp_crq {int /*<<< orphan*/  format; int /*<<< orphan*/  valid; } ;
struct TYPE_2__ {int /*<<< orphan*/  unit_id; } ;
struct scsi_info {TYPE_1__ dds; } ;

/* Variables and functions */
 size_t MSG_HI ; 
 size_t MSG_LOW ; 
 int /*<<< orphan*/  VALID_INIT_MSG ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 long h_send_crq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static long ibmvscsis_send_init_message(struct scsi_info *vscsi, u8 format)
{
	struct viosrp_crq *crq;
	u64 buffer[2] = { 0, 0 };
	long rc;

	crq = (struct viosrp_crq *)&buffer;
	crq->valid = VALID_INIT_MSG;
	crq->format = format;
	rc = h_send_crq(vscsi->dds.unit_id, cpu_to_be64(buffer[MSG_HI]),
			cpu_to_be64(buffer[MSG_LOW]));

	return rc;
}