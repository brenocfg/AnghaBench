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
typedef  int u32 ;
struct kwqe {int kwqe_op_flag; } ;
struct cnic_dev {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CNIC_F_CNIC_UP ; 
 int EAGAIN ; 
 int EINVAL ; 
#define  KWQE_FLAGS_LAYER_MASK_L2 131 
#define  KWQE_FLAGS_LAYER_MASK_L4 130 
#define  KWQE_FLAGS_LAYER_MASK_L5_FCOE 129 
#define  KWQE_FLAGS_LAYER_MASK_L5_ISCSI 128 
 int KWQE_LAYER_MASK ; 
 int cnic_submit_bnx2x_fcoe_kwqes (struct cnic_dev*,struct kwqe**,int) ; 
 int cnic_submit_bnx2x_iscsi_kwqes (struct cnic_dev*,struct kwqe**,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cnic_submit_bnx2x_kwqes(struct cnic_dev *dev, struct kwqe *wqes[],
				   u32 num_wqes)
{
	int ret = -EINVAL;
	u32 layer_code;

	if (!test_bit(CNIC_F_CNIC_UP, &dev->flags))
		return -EAGAIN;		/* bnx2x is down */

	if (!num_wqes)
		return 0;

	layer_code = wqes[0]->kwqe_op_flag & KWQE_LAYER_MASK;
	switch (layer_code) {
	case KWQE_FLAGS_LAYER_MASK_L5_ISCSI:
	case KWQE_FLAGS_LAYER_MASK_L4:
	case KWQE_FLAGS_LAYER_MASK_L2:
		ret = cnic_submit_bnx2x_iscsi_kwqes(dev, wqes, num_wqes);
		break;

	case KWQE_FLAGS_LAYER_MASK_L5_FCOE:
		ret = cnic_submit_bnx2x_fcoe_kwqes(dev, wqes, num_wqes);
		break;
	}
	return ret;
}