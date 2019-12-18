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
struct trf7970a {int state; int aborting; int ignore_timeout; int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; int /*<<< orphan*/  timeout_work; } ;
struct nfc_digital_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECANCELED ; 
#define  TRF7970A_ST_LISTENING 132 
#define  TRF7970A_ST_WAIT_FOR_RX_DATA 131 
#define  TRF7970A_ST_WAIT_FOR_RX_DATA_CONT 130 
#define  TRF7970A_ST_WAIT_FOR_TX_FIFO 129 
#define  TRF7970A_ST_WAIT_TO_ISSUE_EOF 128 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct trf7970a* nfc_digital_get_drvdata (struct nfc_digital_dev*) ; 
 int /*<<< orphan*/  trf7970a_send_err_upstream (struct trf7970a*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void trf7970a_abort_cmd(struct nfc_digital_dev *ddev)
{
	struct trf7970a *trf = nfc_digital_get_drvdata(ddev);

	dev_dbg(trf->dev, "Abort process initiated\n");

	mutex_lock(&trf->lock);

	switch (trf->state) {
	case TRF7970A_ST_WAIT_FOR_TX_FIFO:
	case TRF7970A_ST_WAIT_FOR_RX_DATA:
	case TRF7970A_ST_WAIT_FOR_RX_DATA_CONT:
	case TRF7970A_ST_WAIT_TO_ISSUE_EOF:
		trf->aborting = true;
		break;
	case TRF7970A_ST_LISTENING:
		trf->ignore_timeout = !cancel_delayed_work(&trf->timeout_work);
		trf7970a_send_err_upstream(trf, -ECANCELED);
		dev_dbg(trf->dev, "Abort process complete\n");
		break;
	default:
		break;
	}

	mutex_unlock(&trf->lock);
}