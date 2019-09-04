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
struct request_queue {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int /*<<< orphan*/  blk_queue_scsi_passthrough (struct request_queue*) ; 
 int bsg_register_queue (struct request_queue*,struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bsg_scsi_ops ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 

int bsg_scsi_register_queue(struct request_queue *q, struct device *parent)
{
	if (!blk_queue_scsi_passthrough(q)) {
		WARN_ONCE(true, "Attempt to register a non-SCSI queue\n");
		return -EINVAL;
	}

	return bsg_register_queue(q, parent, dev_name(parent), &bsg_scsi_ops);
}