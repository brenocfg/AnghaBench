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
struct adb_request {int nbytes; int* data; int sent; int reply_len; int* reply; void (* done ) (struct adb_request*) ;int complete; struct adb_request* next; scalar_t__ reply_expected; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_11__ {int /*<<< orphan*/  r; } ;
struct TYPE_10__ {int /*<<< orphan*/  r; } ;
struct TYPE_9__ {int /*<<< orphan*/  r; } ;
struct TYPE_7__ {int /*<<< orphan*/  r; } ;
struct TYPE_12__ {TYPE_5__ intr; TYPE_4__ error; TYPE_3__ dcount; TYPE_2__* data; TYPE_1__ ctrl; } ;
struct TYPE_8__ {int /*<<< orphan*/  r; } ;

/* Variables and functions */
 int APD ; 
 int CRE ; 
 int DFB ; 
 int DTB ; 
 int HMB ; 
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 int TAG ; 
 int TAR ; 
 TYPE_6__* adb ; 
 int /*<<< orphan*/  adb_input (unsigned char*,int,int) ; 
 struct adb_request* current_req ; 
 int in_8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  macio_lock ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  out_8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 void stub1 (struct adb_request*) ; 

__attribute__((used)) static irqreturn_t macio_adb_interrupt(int irq, void *arg)
{
	int i, n, err;
	struct adb_request *req = NULL;
	unsigned char ibuf[16];
	int ibuf_len = 0;
	int complete = 0;
	int autopoll = 0;
	int handled = 0;

	spin_lock(&macio_lock);
	if (in_8(&adb->intr.r) & TAG) {
		handled = 1;
		if ((req = current_req) != 0) {
			/* put the current request in */
			for (i = 0; i < req->nbytes; ++i)
				out_8(&adb->data[i].r, req->data[i]);
			out_8(&adb->dcount.r, req->nbytes & HMB);
			req->sent = 1;
			if (req->reply_expected) {
				out_8(&adb->ctrl.r, DTB + CRE);
			} else {
				out_8(&adb->ctrl.r, DTB);
				current_req = req->next;
				complete = 1;
				if (current_req)
					out_8(&adb->ctrl.r, in_8(&adb->ctrl.r) | TAR);
			}
		}
		out_8(&adb->intr.r, 0);
	}

	if (in_8(&adb->intr.r) & DFB) {
		handled = 1;
		err = in_8(&adb->error.r);
		if (current_req && current_req->sent) {
			/* this is the response to a command */
			req = current_req;
			if (err == 0) {
				req->reply_len = in_8(&adb->dcount.r) & HMB;
				for (i = 0; i < req->reply_len; ++i)
					req->reply[i] = in_8(&adb->data[i].r);
			}
			current_req = req->next;
			complete = 1;
			if (current_req)
				out_8(&adb->ctrl.r, in_8(&adb->ctrl.r) | TAR);
		} else if (err == 0) {
			/* autopoll data */
			n = in_8(&adb->dcount.r) & HMB;
			for (i = 0; i < n; ++i)
				ibuf[i] = in_8(&adb->data[i].r);
			ibuf_len = n;
			autopoll = (in_8(&adb->dcount.r) & APD) != 0;
		}
		out_8(&adb->error.r, 0);
		out_8(&adb->intr.r, 0);
	}
	spin_unlock(&macio_lock);
	if (complete && req) {
	    void (*done)(struct adb_request *) = req->done;
	    mb();
	    req->complete = 1;
	    /* Here, we assume that if the request has a done member, the
    	     * struct request will survive to setting req->complete to 1
	     */
	    if (done)
		(*done)(req);
	}
	if (ibuf_len)
		adb_input(ibuf, ibuf_len, autopoll);

	return IRQ_RETVAL(handled);
}