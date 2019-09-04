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
typedef  int /*<<< orphan*/  u32 ;
struct kcq_info {int /*<<< orphan*/ * status_idx_ptr; } ;
struct cnic_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  barrier () ; 
 int cnic_get_kcqes (struct cnic_dev*,struct kcq_info*) ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  service_kcqes (struct cnic_dev*,int) ; 

__attribute__((used)) static u32 cnic_service_bnx2x_kcq(struct cnic_dev *dev, struct kcq_info *info)
{
	u32 last_status = *info->status_idx_ptr;
	int kcqe_cnt;

	/* status block index must be read before reading the KCQ */
	rmb();
	while ((kcqe_cnt = cnic_get_kcqes(dev, info))) {

		service_kcqes(dev, kcqe_cnt);

		/* Tell compiler that sblk fields can change. */
		barrier();

		last_status = *info->status_idx_ptr;
		/* status block index must be read before reading the KCQ */
		rmb();
	}
	return last_status;
}