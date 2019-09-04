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
struct kwqe {int /*<<< orphan*/  kwqe_op_flag; } ;
struct cnic_dev {int /*<<< orphan*/  netdev; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CNIC_F_CNIC_UP ; 
 int EAGAIN ; 
 int EIO ; 
#define  ISCSI_KWQE_OPCODE_DESTROY_CONN 138 
#define  ISCSI_KWQE_OPCODE_INIT1 137 
#define  ISCSI_KWQE_OPCODE_INIT2 136 
#define  ISCSI_KWQE_OPCODE_OFFLOAD_CONN1 135 
#define  ISCSI_KWQE_OPCODE_UPDATE_CONN 134 
 int KWQE_OPCODE (int /*<<< orphan*/ ) ; 
#define  L4_KWQE_OPCODE_VALUE_CLOSE 133 
#define  L4_KWQE_OPCODE_VALUE_CONNECT1 132 
#define  L4_KWQE_OPCODE_VALUE_OFFLOAD_PG 131 
#define  L4_KWQE_OPCODE_VALUE_RESET 130 
#define  L4_KWQE_OPCODE_VALUE_UPDATE_PG 129 
#define  L4_KWQE_OPCODE_VALUE_UPLOAD_PG 128 
 int cnic_bnx2x_close (struct cnic_dev*,struct kwqe*) ; 
 int cnic_bnx2x_connect (struct cnic_dev*,struct kwqe**,int,int*) ; 
 int cnic_bnx2x_iscsi_destroy (struct cnic_dev*,struct kwqe*) ; 
 int cnic_bnx2x_iscsi_init1 (struct cnic_dev*,struct kwqe*) ; 
 int cnic_bnx2x_iscsi_init2 (struct cnic_dev*,struct kwqe*) ; 
 int cnic_bnx2x_iscsi_ofld1 (struct cnic_dev*,struct kwqe**,int,int*) ; 
 int cnic_bnx2x_iscsi_update (struct cnic_dev*,struct kwqe*) ; 
 int /*<<< orphan*/  cnic_bnx2x_kwqe_err (struct cnic_dev*,struct kwqe*) ; 
 int cnic_bnx2x_offload_pg (struct cnic_dev*,struct kwqe*) ; 
 int cnic_bnx2x_reset (struct cnic_dev*,struct kwqe*) ; 
 int cnic_bnx2x_update_pg (struct cnic_dev*,struct kwqe*) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cnic_submit_bnx2x_iscsi_kwqes(struct cnic_dev *dev,
					 struct kwqe *wqes[], u32 num_wqes)
{
	int i, work, ret;
	u32 opcode;
	struct kwqe *kwqe;

	if (!test_bit(CNIC_F_CNIC_UP, &dev->flags))
		return -EAGAIN;		/* bnx2 is down */

	for (i = 0; i < num_wqes; ) {
		kwqe = wqes[i];
		opcode = KWQE_OPCODE(kwqe->kwqe_op_flag);
		work = 1;

		switch (opcode) {
		case ISCSI_KWQE_OPCODE_INIT1:
			ret = cnic_bnx2x_iscsi_init1(dev, kwqe);
			break;
		case ISCSI_KWQE_OPCODE_INIT2:
			ret = cnic_bnx2x_iscsi_init2(dev, kwqe);
			break;
		case ISCSI_KWQE_OPCODE_OFFLOAD_CONN1:
			ret = cnic_bnx2x_iscsi_ofld1(dev, &wqes[i],
						     num_wqes - i, &work);
			break;
		case ISCSI_KWQE_OPCODE_UPDATE_CONN:
			ret = cnic_bnx2x_iscsi_update(dev, kwqe);
			break;
		case ISCSI_KWQE_OPCODE_DESTROY_CONN:
			ret = cnic_bnx2x_iscsi_destroy(dev, kwqe);
			break;
		case L4_KWQE_OPCODE_VALUE_CONNECT1:
			ret = cnic_bnx2x_connect(dev, &wqes[i], num_wqes - i,
						 &work);
			break;
		case L4_KWQE_OPCODE_VALUE_CLOSE:
			ret = cnic_bnx2x_close(dev, kwqe);
			break;
		case L4_KWQE_OPCODE_VALUE_RESET:
			ret = cnic_bnx2x_reset(dev, kwqe);
			break;
		case L4_KWQE_OPCODE_VALUE_OFFLOAD_PG:
			ret = cnic_bnx2x_offload_pg(dev, kwqe);
			break;
		case L4_KWQE_OPCODE_VALUE_UPDATE_PG:
			ret = cnic_bnx2x_update_pg(dev, kwqe);
			break;
		case L4_KWQE_OPCODE_VALUE_UPLOAD_PG:
			ret = 0;
			break;
		default:
			ret = 0;
			netdev_err(dev->netdev, "Unknown type of KWQE(0x%x)\n",
				   opcode);
			break;
		}
		if (ret < 0) {
			netdev_err(dev->netdev, "KWQE(0x%x) failed\n",
				   opcode);

			/* Possibly bnx2x parity error, send completion
			 * to ulp drivers with error code to speed up
			 * cleanup and reset recovery.
			 */
			if (ret == -EIO || ret == -EAGAIN)
				cnic_bnx2x_kwqe_err(dev, kwqe);
		}
		i += work;
	}
	return 0;
}