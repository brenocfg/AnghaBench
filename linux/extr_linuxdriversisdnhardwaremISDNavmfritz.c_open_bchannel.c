#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct fritzcard {struct bchannel* bch; } ;
struct TYPE_4__ {int channel; } ;
struct channel_req {scalar_t__ protocol; TYPE_1__* ch; TYPE_2__ adr; } ;
struct TYPE_3__ {scalar_t__ protocol; } ;
struct bchannel {TYPE_1__ ch; int /*<<< orphan*/  Flags; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  FLG_OPEN ; 
 scalar_t__ ISDN_P_NONE ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
open_bchannel(struct fritzcard *fc, struct channel_req *rq)
{
	struct bchannel		*bch;

	if (rq->adr.channel == 0 || rq->adr.channel > 2)
		return -EINVAL;
	if (rq->protocol == ISDN_P_NONE)
		return -EINVAL;
	bch = &fc->bch[rq->adr.channel - 1];
	if (test_and_set_bit(FLG_OPEN, &bch->Flags))
		return -EBUSY; /* b-channel can be only open once */
	bch->ch.protocol = rq->protocol;
	rq->ch = &bch->ch;
	return 0;
}