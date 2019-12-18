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
struct TYPE_3__ {scalar_t__ hi; scalar_t__ lo; } ;
struct scsi_sge {scalar_t__ sge_len; TYPE_1__ sge_addr; } ;
struct scsi_cmnd {int dummy; } ;
struct qedf_ioreq {TYPE_2__* bd_tbl; struct scsi_cmnd* sc_cmd; } ;
struct TYPE_4__ {int bd_valid; struct scsi_sge* bd_tbl; } ;

/* Variables and functions */
 int ENOMEM ; 
 int qedf_map_sg (struct qedf_ioreq*) ; 
 scalar_t__ scsi_sg_count (struct scsi_cmnd*) ; 

__attribute__((used)) static int qedf_build_bd_list_from_sg(struct qedf_ioreq *io_req)
{
	struct scsi_cmnd *sc = io_req->sc_cmd;
	struct scsi_sge *bd = io_req->bd_tbl->bd_tbl;
	int bd_count;

	if (scsi_sg_count(sc)) {
		bd_count = qedf_map_sg(io_req);
		if (bd_count == 0)
			return -ENOMEM;
	} else {
		bd_count = 0;
		bd[0].sge_addr.lo = bd[0].sge_addr.hi = 0;
		bd[0].sge_len = 0;
	}
	io_req->bd_tbl->bd_valid = bd_count;

	return 0;
}