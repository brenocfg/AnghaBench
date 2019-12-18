#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct req_que {scalar_t__ ring_index; scalar_t__ length; scalar_t__ ring_ptr; scalar_t__ ring; } ;
struct TYPE_5__ {int /*<<< orphan*/  hw; } ;
typedef  TYPE_1__ scsi_qla_host_t ;
struct TYPE_6__ {int /*<<< orphan*/  entry_type; } ;
typedef  TYPE_2__ cont_a64_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONTINUE_A64_TYPE ; 
 int /*<<< orphan*/  CONTINUE_A64_TYPE_FX00 ; 
 scalar_t__ IS_QLAFX00 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_unaligned_le32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline cont_a64_entry_t *
qla2x00_prep_cont_type1_iocb(scsi_qla_host_t *vha, struct req_que *req)
{
	cont_a64_entry_t *cont_pkt;

	/* Adjust ring index. */
	req->ring_index++;
	if (req->ring_index == req->length) {
		req->ring_index = 0;
		req->ring_ptr = req->ring;
	} else {
		req->ring_ptr++;
	}

	cont_pkt = (cont_a64_entry_t *)req->ring_ptr;

	/* Load packet defaults. */
	put_unaligned_le32(IS_QLAFX00(vha->hw) ? CONTINUE_A64_TYPE_FX00 :
			   CONTINUE_A64_TYPE, &cont_pkt->entry_type);

	return (cont_pkt);
}