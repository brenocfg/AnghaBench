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
struct scsi_device {struct alua_dh_data* handler_data; } ;
struct request {int /*<<< orphan*/  rq_flags; } ;
struct alua_port_group {unsigned char state; } ;
struct alua_dh_data {int /*<<< orphan*/  pg; } ;
typedef  int /*<<< orphan*/  blk_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int /*<<< orphan*/  BLK_STS_OK ; 
 int /*<<< orphan*/  BLK_STS_RESOURCE ; 
 int /*<<< orphan*/  RQF_QUIET ; 
#define  SCSI_ACCESS_STATE_ACTIVE 131 
#define  SCSI_ACCESS_STATE_LBA 130 
#define  SCSI_ACCESS_STATE_OPTIMAL 129 
#define  SCSI_ACCESS_STATE_TRANSITIONING 128 
 struct alua_port_group* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static blk_status_t alua_prep_fn(struct scsi_device *sdev, struct request *req)
{
	struct alua_dh_data *h = sdev->handler_data;
	struct alua_port_group *pg;
	unsigned char state = SCSI_ACCESS_STATE_OPTIMAL;

	rcu_read_lock();
	pg = rcu_dereference(h->pg);
	if (pg)
		state = pg->state;
	rcu_read_unlock();

	switch (state) {
	case SCSI_ACCESS_STATE_OPTIMAL:
	case SCSI_ACCESS_STATE_ACTIVE:
	case SCSI_ACCESS_STATE_LBA:
		return BLK_STS_OK;
	case SCSI_ACCESS_STATE_TRANSITIONING:
		return BLK_STS_RESOURCE;
	default:
		req->rq_flags |= RQF_QUIET;
		return BLK_STS_IOERR;
	}
}