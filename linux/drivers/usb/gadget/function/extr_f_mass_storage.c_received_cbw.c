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
struct usb_request {scalar_t__ actual; scalar_t__ status; struct bulk_cb_wrap* buf; } ;
struct fsg_dev {int /*<<< orphan*/  bulk_out; int /*<<< orphan*/  atomic_bitflags; struct fsg_common* common; } ;
struct fsg_common {scalar_t__ cmnd_size; scalar_t__ data_size; scalar_t__ lun; int /*<<< orphan*/  tag; int /*<<< orphan*/ * curlun; int /*<<< orphan*/ ** luns; int /*<<< orphan*/  data_dir; int /*<<< orphan*/  cmnd; scalar_t__ can_stall; } ;
struct fsg_buffhd {struct usb_request* outreq; } ;
struct bulk_cb_wrap {scalar_t__ Signature; scalar_t__ Lun; int Flags; scalar_t__ Length; scalar_t__ DataTransferLength; int /*<<< orphan*/  Tag; int /*<<< orphan*/  CDB; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  DATA_DIR_FROM_HOST ; 
 int /*<<< orphan*/  DATA_DIR_NONE ; 
 int /*<<< orphan*/  DATA_DIR_TO_HOST ; 
 int /*<<< orphan*/  DBG (struct fsg_dev*,char*,scalar_t__,int,...) ; 
 int EINVAL ; 
 int /*<<< orphan*/  IGNORE_BULK_OUT ; 
 scalar_t__ MAX_COMMAND_SIZE ; 
 int /*<<< orphan*/  US_BULK_CB_SIGN ; 
 scalar_t__ US_BULK_CB_WRAP_LEN ; 
 int US_BULK_FLAG_IN ; 
 scalar_t__ cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsg_set_halt (struct fsg_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  halt_bulk_in_endpoint (struct fsg_dev*) ; 
 scalar_t__ le32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wedge_bulk_in_endpoint (struct fsg_dev*) ; 

__attribute__((used)) static int received_cbw(struct fsg_dev *fsg, struct fsg_buffhd *bh)
{
	struct usb_request	*req = bh->outreq;
	struct bulk_cb_wrap	*cbw = req->buf;
	struct fsg_common	*common = fsg->common;

	/* Was this a real packet?  Should it be ignored? */
	if (req->status || test_bit(IGNORE_BULK_OUT, &fsg->atomic_bitflags))
		return -EINVAL;

	/* Is the CBW valid? */
	if (req->actual != US_BULK_CB_WRAP_LEN ||
			cbw->Signature != cpu_to_le32(
				US_BULK_CB_SIGN)) {
		DBG(fsg, "invalid CBW: len %u sig 0x%x\n",
				req->actual,
				le32_to_cpu(cbw->Signature));

		/*
		 * The Bulk-only spec says we MUST stall the IN endpoint
		 * (6.6.1), so it's unavoidable.  It also says we must
		 * retain this state until the next reset, but there's
		 * no way to tell the controller driver it should ignore
		 * Clear-Feature(HALT) requests.
		 *
		 * We aren't required to halt the OUT endpoint; instead
		 * we can simply accept and discard any data received
		 * until the next reset.
		 */
		wedge_bulk_in_endpoint(fsg);
		set_bit(IGNORE_BULK_OUT, &fsg->atomic_bitflags);
		return -EINVAL;
	}

	/* Is the CBW meaningful? */
	if (cbw->Lun >= ARRAY_SIZE(common->luns) ||
	    cbw->Flags & ~US_BULK_FLAG_IN || cbw->Length <= 0 ||
	    cbw->Length > MAX_COMMAND_SIZE) {
		DBG(fsg, "non-meaningful CBW: lun = %u, flags = 0x%x, "
				"cmdlen %u\n",
				cbw->Lun, cbw->Flags, cbw->Length);

		/*
		 * We can do anything we want here, so let's stall the
		 * bulk pipes if we are allowed to.
		 */
		if (common->can_stall) {
			fsg_set_halt(fsg, fsg->bulk_out);
			halt_bulk_in_endpoint(fsg);
		}
		return -EINVAL;
	}

	/* Save the command for later */
	common->cmnd_size = cbw->Length;
	memcpy(common->cmnd, cbw->CDB, common->cmnd_size);
	if (cbw->Flags & US_BULK_FLAG_IN)
		common->data_dir = DATA_DIR_TO_HOST;
	else
		common->data_dir = DATA_DIR_FROM_HOST;
	common->data_size = le32_to_cpu(cbw->DataTransferLength);
	if (common->data_size == 0)
		common->data_dir = DATA_DIR_NONE;
	common->lun = cbw->Lun;
	if (common->lun < ARRAY_SIZE(common->luns))
		common->curlun = common->luns[common->lun];
	else
		common->curlun = NULL;
	common->tag = cbw->Tag;
	return 0;
}