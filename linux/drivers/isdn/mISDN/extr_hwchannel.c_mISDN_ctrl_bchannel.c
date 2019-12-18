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
struct mISDN_ctrl_req {int op; int p1; int p2; } ;
struct bchannel {int dropcnt; int next_maxlen; int next_minlen; int minlen; int maxlen; int /*<<< orphan*/  Flags; int /*<<< orphan*/  fill; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FLG_FILLEMPTY ; 
 int /*<<< orphan*/  FLG_RX_OFF ; 
 int /*<<< orphan*/  MISDN_BCH_FILL_SIZE ; 
#define  MISDN_CTRL_FILL_EMPTY 131 
#define  MISDN_CTRL_GETOP 130 
#define  MISDN_CTRL_RX_BUFFER 129 
#define  MISDN_CTRL_RX_OFF 128 
 int MISDN_CTRL_RX_SIZE_IGNORE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
mISDN_ctrl_bchannel(struct bchannel *bch, struct mISDN_ctrl_req *cq)
{
	int ret = 0;

	switch (cq->op) {
	case MISDN_CTRL_GETOP:
		cq->op = MISDN_CTRL_RX_BUFFER | MISDN_CTRL_FILL_EMPTY |
			 MISDN_CTRL_RX_OFF;
		break;
	case MISDN_CTRL_FILL_EMPTY:
		if (cq->p1) {
			memset(bch->fill, cq->p2 & 0xff, MISDN_BCH_FILL_SIZE);
			test_and_set_bit(FLG_FILLEMPTY, &bch->Flags);
		} else {
			test_and_clear_bit(FLG_FILLEMPTY, &bch->Flags);
		}
		break;
	case MISDN_CTRL_RX_OFF:
		/* read back dropped byte count */
		cq->p2 = bch->dropcnt;
		if (cq->p1)
			test_and_set_bit(FLG_RX_OFF, &bch->Flags);
		else
			test_and_clear_bit(FLG_RX_OFF, &bch->Flags);
		bch->dropcnt = 0;
		break;
	case MISDN_CTRL_RX_BUFFER:
		if (cq->p2 > MISDN_CTRL_RX_SIZE_IGNORE)
			bch->next_maxlen = cq->p2;
		if (cq->p1 > MISDN_CTRL_RX_SIZE_IGNORE)
			bch->next_minlen = cq->p1;
		/* we return the old values */
		cq->p1 = bch->minlen;
		cq->p2 = bch->maxlen;
		break;
	default:
		pr_info("mISDN unhandled control %x operation\n", cq->op);
		ret = -EINVAL;
		break;
	}
	return ret;
}