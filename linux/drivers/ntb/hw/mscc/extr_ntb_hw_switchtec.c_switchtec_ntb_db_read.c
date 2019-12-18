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
typedef  int u64 ;
struct switchtec_ntb {int db_shift; int db_valid_mask; TYPE_1__* mmio_self_dbmsg; } ;
struct ntb_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  idb; } ;

/* Variables and functions */
 int ioread64 (int /*<<< orphan*/ *) ; 
 struct switchtec_ntb* ntb_sndev (struct ntb_dev*) ; 

__attribute__((used)) static u64 switchtec_ntb_db_read(struct ntb_dev *ntb)
{
	u64 ret;
	struct switchtec_ntb *sndev = ntb_sndev(ntb);

	ret = ioread64(&sndev->mmio_self_dbmsg->idb) >> sndev->db_shift;

	return ret & sndev->db_valid_mask;
}