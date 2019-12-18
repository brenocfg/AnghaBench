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
struct fc_rport {int dummy; } ;
struct bsg_job {int dummy; } ;
typedef  int blk_status_t ;

/* Variables and functions */
#define  BLK_STS_OK 129 
#define  BLK_STS_RESOURCE 128 
 int EAGAIN ; 
 int EIO ; 
 int fc_bsg_dispatch (struct bsg_job*) ; 
 int fc_bsg_rport_prep (struct fc_rport*) ; 
 struct fc_rport* fc_bsg_to_rport (struct bsg_job*) ; 

__attribute__((used)) static int fc_bsg_dispatch_prep(struct bsg_job *job)
{
	struct fc_rport *rport = fc_bsg_to_rport(job);
	blk_status_t ret;

	ret = fc_bsg_rport_prep(rport);
	switch (ret) {
	case BLK_STS_OK:
		break;
	case BLK_STS_RESOURCE:
		return -EAGAIN;
	default:
		return -EIO;
	}

	return fc_bsg_dispatch(job);
}