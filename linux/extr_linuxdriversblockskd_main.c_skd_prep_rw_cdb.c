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
struct skd_scsi_request {unsigned int* cdb; } ;

/* Variables and functions */
 int READ ; 
 unsigned int READ_10 ; 
 unsigned int WRITE_10 ; 

__attribute__((used)) static void
skd_prep_rw_cdb(struct skd_scsi_request *scsi_req,
		int data_dir, unsigned lba,
		unsigned count)
{
	if (data_dir == READ)
		scsi_req->cdb[0] = READ_10;
	else
		scsi_req->cdb[0] = WRITE_10;

	scsi_req->cdb[1] = 0;
	scsi_req->cdb[2] = (lba & 0xff000000) >> 24;
	scsi_req->cdb[3] = (lba & 0xff0000) >> 16;
	scsi_req->cdb[4] = (lba & 0xff00) >> 8;
	scsi_req->cdb[5] = (lba & 0xff);
	scsi_req->cdb[6] = 0;
	scsi_req->cdb[7] = (count & 0xff00) >> 8;
	scsi_req->cdb[8] = count & 0xff;
	scsi_req->cdb[9] = 0;
}