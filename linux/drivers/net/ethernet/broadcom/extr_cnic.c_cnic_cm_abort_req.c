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
struct l4_kwq_reset_req {int flags; int /*<<< orphan*/  cid; int /*<<< orphan*/  op_code; } ;
struct kwqe {int dummy; } ;
struct cnic_sock {int /*<<< orphan*/  cid; int /*<<< orphan*/  kwqe2; struct cnic_dev* dev; } ;
struct cnic_dev {int (* submit_kwqes ) (struct cnic_dev*,struct kwqe**,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  L4_KWQE_OPCODE_VALUE_RESET ; 
 int L4_KWQ_RESET_REQ_LAYER_CODE_SHIFT ; 
 int L4_LAYER_CODE ; 
 int /*<<< orphan*/  memset (struct l4_kwq_reset_req*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct cnic_dev*,struct kwqe**,int) ; 

__attribute__((used)) static int cnic_cm_abort_req(struct cnic_sock *csk)
{
	struct cnic_dev *dev = csk->dev;
	struct l4_kwq_reset_req *l4kwqe;
	struct kwqe *wqes[1];

	l4kwqe = (struct l4_kwq_reset_req *) &csk->kwqe2;
	memset(l4kwqe, 0, sizeof(*l4kwqe));
	wqes[0] = (struct kwqe *) l4kwqe;

	l4kwqe->op_code = L4_KWQE_OPCODE_VALUE_RESET;
	l4kwqe->flags = L4_LAYER_CODE << L4_KWQ_RESET_REQ_LAYER_CODE_SHIFT;
	l4kwqe->cid = csk->cid;

	return dev->submit_kwqes(dev, wqes, 1);
}