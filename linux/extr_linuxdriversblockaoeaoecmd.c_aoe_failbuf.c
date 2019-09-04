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
struct TYPE_3__ {scalar_t__ bi_size; } ;
struct buf {scalar_t__ nframesout; TYPE_2__* bio; TYPE_1__ iter; } ;
struct aoedev {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  bi_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int /*<<< orphan*/  aoe_end_buf (struct aoedev*,struct buf*) ; 

void
aoe_failbuf(struct aoedev *d, struct buf *buf)
{
	if (buf == NULL)
		return;
	buf->iter.bi_size = 0;
	buf->bio->bi_status = BLK_STS_IOERR;
	if (buf->nframesout == 0)
		aoe_end_buf(d, buf);
}