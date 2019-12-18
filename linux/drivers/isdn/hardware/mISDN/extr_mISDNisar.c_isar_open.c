#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct isar_hw {TYPE_1__* ch; } ;
struct TYPE_6__ {int channel; } ;
struct channel_req {scalar_t__ protocol; TYPE_2__* ch; TYPE_3__ adr; } ;
struct TYPE_5__ {scalar_t__ protocol; } ;
struct bchannel {TYPE_2__ ch; int /*<<< orphan*/  Flags; } ;
struct TYPE_4__ {struct bchannel bch; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  FLG_OPEN ; 
 scalar_t__ ISDN_P_NONE ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
isar_open(struct isar_hw *isar, struct channel_req *rq)
{
	struct bchannel		*bch;

	if (rq->adr.channel == 0 || rq->adr.channel > 2)
		return -EINVAL;
	if (rq->protocol == ISDN_P_NONE)
		return -EINVAL;
	bch = &isar->ch[rq->adr.channel - 1].bch;
	if (test_and_set_bit(FLG_OPEN, &bch->Flags))
		return -EBUSY; /* b-channel can be only open once */
	bch->ch.protocol = rq->protocol;
	rq->ch = &bch->ch;
	return 0;
}