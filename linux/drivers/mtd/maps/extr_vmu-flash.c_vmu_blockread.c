#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct memcard {int blocklen; int readcnt; int /*<<< orphan*/  blockread; } ;
struct mapleq {TYPE_1__* recvbuf; struct maple_device* dev; } ;
struct maple_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ buf; } ;

/* Variables and functions */
 struct memcard* maple_get_drvdata (struct maple_device*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void vmu_blockread(struct mapleq *mq)
{
	struct maple_device *mdev;
	struct memcard *card;

	mdev = mq->dev;
	card = maple_get_drvdata(mdev);
	/* copy the read in data */

	if (unlikely(!card->blockread))
		return;

	memcpy(card->blockread, mq->recvbuf->buf + 12,
		card->blocklen/card->readcnt);

}