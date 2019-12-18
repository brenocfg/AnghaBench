#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct fsg_common {int data_dir; TYPE_2__* fsg; int /*<<< orphan*/  can_stall; int /*<<< orphan*/  short_packet_received; int /*<<< orphan*/  residue; struct fsg_buffhd* next_buffhd_to_fill; int /*<<< orphan*/  data_size; } ;
struct fsg_buffhd {struct fsg_buffhd* next; TYPE_1__* inreq; } ;
struct TYPE_5__ {int /*<<< orphan*/  bulk_out; } ;
struct TYPE_4__ {int zero; } ;

/* Variables and functions */
#define  DATA_DIR_FROM_HOST 131 
#define  DATA_DIR_NONE 130 
#define  DATA_DIR_TO_HOST 129 
#define  DATA_DIR_UNKNOWN 128 
 int EINTR ; 
 int EIO ; 
 int /*<<< orphan*/  FSG_STATE_ABORT_BULK_OUT ; 
 int /*<<< orphan*/  fsg_is_set (struct fsg_common*) ; 
 int /*<<< orphan*/  fsg_set_halt (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int halt_bulk_in_endpoint (TYPE_2__*) ; 
 int /*<<< orphan*/  raise_exception (struct fsg_common*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_in_transfer (struct fsg_common*,struct fsg_buffhd*) ; 
 int throw_away_data (struct fsg_common*) ; 

__attribute__((used)) static int finish_reply(struct fsg_common *common)
{
	struct fsg_buffhd	*bh = common->next_buffhd_to_fill;
	int			rc = 0;

	switch (common->data_dir) {
	case DATA_DIR_NONE:
		break;			/* Nothing to send */

	/*
	 * If we don't know whether the host wants to read or write,
	 * this must be CB or CBI with an unknown command.  We mustn't
	 * try to send or receive any data.  So stall both bulk pipes
	 * if we can and wait for a reset.
	 */
	case DATA_DIR_UNKNOWN:
		if (!common->can_stall) {
			/* Nothing */
		} else if (fsg_is_set(common)) {
			fsg_set_halt(common->fsg, common->fsg->bulk_out);
			rc = halt_bulk_in_endpoint(common->fsg);
		} else {
			/* Don't know what to do if common->fsg is NULL */
			rc = -EIO;
		}
		break;

	/* All but the last buffer of data must have already been sent */
	case DATA_DIR_TO_HOST:
		if (common->data_size == 0) {
			/* Nothing to send */

		/* Don't know what to do if common->fsg is NULL */
		} else if (!fsg_is_set(common)) {
			rc = -EIO;

		/* If there's no residue, simply send the last buffer */
		} else if (common->residue == 0) {
			bh->inreq->zero = 0;
			if (!start_in_transfer(common, bh))
				return -EIO;
			common->next_buffhd_to_fill = bh->next;

		/*
		 * For Bulk-only, mark the end of the data with a short
		 * packet.  If we are allowed to stall, halt the bulk-in
		 * endpoint.  (Note: This violates the Bulk-Only Transport
		 * specification, which requires us to pad the data if we
		 * don't halt the endpoint.  Presumably nobody will mind.)
		 */
		} else {
			bh->inreq->zero = 1;
			if (!start_in_transfer(common, bh))
				rc = -EIO;
			common->next_buffhd_to_fill = bh->next;
			if (common->can_stall)
				rc = halt_bulk_in_endpoint(common->fsg);
		}
		break;

	/*
	 * We have processed all we want from the data the host has sent.
	 * There may still be outstanding bulk-out requests.
	 */
	case DATA_DIR_FROM_HOST:
		if (common->residue == 0) {
			/* Nothing to receive */

		/* Did the host stop sending unexpectedly early? */
		} else if (common->short_packet_received) {
			raise_exception(common, FSG_STATE_ABORT_BULK_OUT);
			rc = -EINTR;

		/*
		 * We haven't processed all the incoming data.  Even though
		 * we may be allowed to stall, doing so would cause a race.
		 * The controller may already have ACK'ed all the remaining
		 * bulk-out packets, in which case the host wouldn't see a
		 * STALL.  Not realizing the endpoint was halted, it wouldn't
		 * clear the halt -- leading to problems later on.
		 */
#if 0
		} else if (common->can_stall) {
			if (fsg_is_set(common))
				fsg_set_halt(common->fsg,
					     common->fsg->bulk_out);
			raise_exception(common, FSG_STATE_ABORT_BULK_OUT);
			rc = -EINTR;
#endif

		/*
		 * We can't stall.  Read in the excess data and throw it
		 * all away.
		 */
		} else {
			rc = throw_away_data(common);
		}
		break;
	}
	return rc;
}