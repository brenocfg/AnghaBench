#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_10__ {void* rb_base; int size; scalar_t__ current_read_offset; } ;
struct scif_qp {TYPE_4__ inbound_q; int /*<<< orphan*/  local_write; TYPE_3__* remote_qp; scalar_t__ local_read; TYPE_4__ outbound_q; } ;
struct scif_dev {int /*<<< orphan*/  node; TYPE_1__* sdev; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;
struct TYPE_12__ {int /*<<< orphan*/  node; } ;
struct TYPE_11__ {size_t nodeid; } ;
struct TYPE_8__ {int size; } ;
struct TYPE_9__ {scalar_t__ magic; scalar_t__ local_read; int /*<<< orphan*/  local_write; TYPE_2__ inbound_q; int /*<<< orphan*/  local_buf; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int ENODEV ; 
 int ENOMEM ; 
 scalar_t__ SCIFEP_MAGIC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_count_order (int) ; 
 TYPE_6__* scif_dev ; 
 TYPE_5__ scif_info ; 
 void* scif_ioremap (int /*<<< orphan*/ ,int,struct scif_dev*) ; 
 int /*<<< orphan*/  scif_rb_init (TYPE_4__*,scalar_t__*,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 

int scif_setup_qp_connect_response(struct scif_dev *scifdev,
				   struct scif_qp *qp, u64 payload)
{
	int err = 0;
	void *r_buf;
	int remote_size;
	phys_addr_t tmp_phys;

	qp->remote_qp = scif_ioremap(payload, sizeof(struct scif_qp), scifdev);

	if (!qp->remote_qp) {
		err = -ENOMEM;
		goto error;
	}

	if (qp->remote_qp->magic != SCIFEP_MAGIC) {
		dev_err(&scifdev->sdev->dev,
			"SCIFEP_MAGIC mismatch between self %d remote %d\n",
			scif_dev[scif_info.nodeid].node, scifdev->node);
		err = -ENODEV;
		goto error;
	}

	tmp_phys = qp->remote_qp->local_buf;
	remote_size = qp->remote_qp->inbound_q.size;
	r_buf = scif_ioremap(tmp_phys, remote_size, scifdev);

	if (!r_buf)
		return -EIO;

	qp->local_read = 0;
	scif_rb_init(&qp->outbound_q,
		     &qp->local_read,
		     &qp->remote_qp->local_write,
		     r_buf,
		     get_count_order(remote_size));
	/*
	 * Because the node QP may already be processing an INIT message, set
	 * the read pointer so the cached read offset isn't lost
	 */
	qp->remote_qp->local_read = qp->inbound_q.current_read_offset;
	/*
	 * resetup the inbound_q now that we know where the
	 * inbound_read really is.
	 */
	scif_rb_init(&qp->inbound_q,
		     &qp->remote_qp->local_read,
		     &qp->local_write,
		     qp->inbound_q.rb_base,
		     get_count_order(qp->inbound_q.size));
error:
	return err;
}