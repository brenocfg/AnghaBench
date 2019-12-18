#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct mv_udc {TYPE_4__* op_regs; TYPE_2__* dev; TYPE_1__* eps; struct mv_dqh* ep_dqh; } ;
struct TYPE_10__ {int length; int actual; } ;
struct mv_req {int dtd_count; TYPE_5__ req; TYPE_3__* ep; struct mv_dtd* head; } ;
struct mv_dtd {int size_ioc_sts; scalar_t__ td_dma; scalar_t__ dtd_next; scalar_t__ next_dtd_virt; } ;
struct mv_dqh {int size_ioc_int_sts; scalar_t__ curr_dtd_ptr; } ;
struct TYPE_9__ {int /*<<< orphan*/  epstatus; } ;
struct TYPE_8__ {int ep_num; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int DTD_ERROR_MASK ; 
 int DTD_LENGTH_BIT_POS ; 
 int DTD_PACKET_SIZE ; 
 int DTD_STATUS_ACTIVE ; 
 int DTD_STATUS_DATA_BUFF_ERR ; 
 int DTD_STATUS_HALTED ; 
 int DTD_STATUS_TRANSACTION_ERR ; 
 int EILSEQ ; 
 int EPIPE ; 
 int EPROTO ; 
 int EP_DIR_OUT ; 
 scalar_t__ EP_QUEUE_HEAD_NEXT_TERMINATE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,char*,int) ; 
 int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int process_ep_req(struct mv_udc *udc, int index,
	struct mv_req *curr_req)
{
	struct mv_dtd	*curr_dtd;
	struct mv_dqh	*curr_dqh;
	int actual, remaining_length;
	int i, direction;
	int retval = 0;
	u32 errors;
	u32 bit_pos;

	curr_dqh = &udc->ep_dqh[index];
	direction = index % 2;

	curr_dtd = curr_req->head;
	actual = curr_req->req.length;

	for (i = 0; i < curr_req->dtd_count; i++) {
		if (curr_dtd->size_ioc_sts & DTD_STATUS_ACTIVE) {
			dev_dbg(&udc->dev->dev, "%s, dTD not completed\n",
				udc->eps[index].name);
			return 1;
		}

		errors = curr_dtd->size_ioc_sts & DTD_ERROR_MASK;
		if (!errors) {
			remaining_length =
				(curr_dtd->size_ioc_sts	& DTD_PACKET_SIZE)
					>> DTD_LENGTH_BIT_POS;
			actual -= remaining_length;

			if (remaining_length) {
				if (direction) {
					dev_dbg(&udc->dev->dev,
						"TX dTD remains data\n");
					retval = -EPROTO;
					break;
				} else
					break;
			}
		} else {
			dev_info(&udc->dev->dev,
				"complete_tr error: ep=%d %s: error = 0x%x\n",
				index >> 1, direction ? "SEND" : "RECV",
				errors);
			if (errors & DTD_STATUS_HALTED) {
				/* Clear the errors and Halt condition */
				curr_dqh->size_ioc_int_sts &= ~errors;
				retval = -EPIPE;
			} else if (errors & DTD_STATUS_DATA_BUFF_ERR) {
				retval = -EPROTO;
			} else if (errors & DTD_STATUS_TRANSACTION_ERR) {
				retval = -EILSEQ;
			}
		}
		if (i != curr_req->dtd_count - 1)
			curr_dtd = (struct mv_dtd *)curr_dtd->next_dtd_virt;
	}
	if (retval)
		return retval;

	if (direction == EP_DIR_OUT)
		bit_pos = 1 << curr_req->ep->ep_num;
	else
		bit_pos = 1 << (16 + curr_req->ep->ep_num);

	while (curr_dqh->curr_dtd_ptr == curr_dtd->td_dma) {
		if (curr_dtd->dtd_next == EP_QUEUE_HEAD_NEXT_TERMINATE) {
			while (readl(&udc->op_regs->epstatus) & bit_pos)
				udelay(1);
			break;
		}
		udelay(1);
	}

	curr_req->req.actual = actual;

	return 0;
}