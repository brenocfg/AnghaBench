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
struct l4_kwq_update_pg {int flags; int /*<<< orphan*/  pg_valids; int /*<<< orphan*/  pg_host_opaque; int /*<<< orphan*/  da5; int /*<<< orphan*/  da4; int /*<<< orphan*/  da3; int /*<<< orphan*/  da2; int /*<<< orphan*/  da1; int /*<<< orphan*/  da0; int /*<<< orphan*/  pg_cid; int /*<<< orphan*/  opcode; } ;
struct kwqe {int dummy; } ;
struct cnic_sock {int /*<<< orphan*/  l5_cid; int /*<<< orphan*/ * ha; int /*<<< orphan*/  pg_cid; int /*<<< orphan*/  kwqe1; struct cnic_dev* dev; } ;
struct cnic_dev {int (* submit_kwqes ) (struct cnic_dev*,struct kwqe**,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  L4_KWQE_OPCODE_VALUE_UPDATE_PG ; 
 int L4_KWQ_UPDATE_PG_LAYER_CODE_SHIFT ; 
 int /*<<< orphan*/  L4_KWQ_UPDATE_PG_VALIDS_DA ; 
 int L4_LAYER_CODE ; 
 int /*<<< orphan*/  memset (struct l4_kwq_update_pg*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct cnic_dev*,struct kwqe**,int) ; 

__attribute__((used)) static int cnic_cm_update_pg(struct cnic_sock *csk)
{
	struct cnic_dev *dev = csk->dev;
	struct l4_kwq_update_pg *l4kwqe;
	struct kwqe *wqes[1];

	l4kwqe = (struct l4_kwq_update_pg *) &csk->kwqe1;
	memset(l4kwqe, 0, sizeof(*l4kwqe));
	wqes[0] = (struct kwqe *) l4kwqe;

	l4kwqe->opcode = L4_KWQE_OPCODE_VALUE_UPDATE_PG;
	l4kwqe->flags =
		L4_LAYER_CODE << L4_KWQ_UPDATE_PG_LAYER_CODE_SHIFT;
	l4kwqe->pg_cid = csk->pg_cid;

	l4kwqe->da0 = csk->ha[0];
	l4kwqe->da1 = csk->ha[1];
	l4kwqe->da2 = csk->ha[2];
	l4kwqe->da3 = csk->ha[3];
	l4kwqe->da4 = csk->ha[4];
	l4kwqe->da5 = csk->ha[5];

	l4kwqe->pg_host_opaque = csk->l5_cid;
	l4kwqe->pg_valids = L4_KWQ_UPDATE_PG_VALIDS_DA;

	return dev->submit_kwqes(dev, wqes, 1);
}