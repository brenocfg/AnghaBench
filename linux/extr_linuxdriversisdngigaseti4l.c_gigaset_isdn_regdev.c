#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct cardstate {int minor_index; void* hw_hdr_len; int /*<<< orphan*/  myid; TYPE_1__* iif; int /*<<< orphan*/  channels; } ;
struct TYPE_5__ {int features; int /*<<< orphan*/  channels; int /*<<< orphan*/ * statcallb; int /*<<< orphan*/ * rcvcallb_skb; int /*<<< orphan*/ * readstat; int /*<<< orphan*/ * writecmd; int /*<<< orphan*/  writebuf_skb; int /*<<< orphan*/  command; void* hl_hdrlen; int /*<<< orphan*/  maxbufsize; int /*<<< orphan*/  owner; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ isdn_if ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* HW_HDR_LEN ; 
 int ISDN_FEATURE_L2_HDLC ; 
 int ISDN_FEATURE_L2_TRANS ; 
 int ISDN_FEATURE_L2_X75I ; 
 int ISDN_FEATURE_L3_TRANS ; 
 int ISDN_FEATURE_P_EURO ; 
 int /*<<< orphan*/  MAX_BUF_SIZE ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  command_from_LL ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 TYPE_1__* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  register_isdn (TYPE_1__*) ; 
 int snprintf (int /*<<< orphan*/ ,int,char*,char const*,int) ; 
 int /*<<< orphan*/  writebuf_from_LL ; 

int gigaset_isdn_regdev(struct cardstate *cs, const char *isdnid)
{
	isdn_if *iif;

	iif = kmalloc(sizeof *iif, GFP_KERNEL);
	if (!iif) {
		pr_err("out of memory\n");
		return -ENOMEM;
	}

	if (snprintf(iif->id, sizeof iif->id, "%s_%u", isdnid, cs->minor_index)
	    >= sizeof iif->id) {
		pr_err("ID too long: %s\n", isdnid);
		kfree(iif);
		return -EINVAL;
	}

	iif->owner = THIS_MODULE;
	iif->channels = cs->channels;
	iif->maxbufsize = MAX_BUF_SIZE;
	iif->features = ISDN_FEATURE_L2_TRANS |
		ISDN_FEATURE_L2_HDLC |
		ISDN_FEATURE_L2_X75I |
		ISDN_FEATURE_L3_TRANS |
		ISDN_FEATURE_P_EURO;
	iif->hl_hdrlen = HW_HDR_LEN;		/* Area for storing ack */
	iif->command = command_from_LL;
	iif->writebuf_skb = writebuf_from_LL;
	iif->writecmd = NULL;			/* Don't support isdnctrl */
	iif->readstat = NULL;			/* Don't support isdnctrl */
	iif->rcvcallb_skb = NULL;		/* Will be set by LL */
	iif->statcallb = NULL;			/* Will be set by LL */

	if (!register_isdn(iif)) {
		pr_err("register_isdn failed\n");
		kfree(iif);
		return -EINVAL;
	}

	cs->iif = iif;
	cs->myid = iif->channels;		/* Set my device id */
	cs->hw_hdr_len = HW_HDR_LEN;
	return 0;
}