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
struct request {int dummy; } ;
struct buf {int /*<<< orphan*/  iter; struct bio* bio; struct request* rq; } ;
struct bio {int /*<<< orphan*/  bi_iter; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct buf*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bufinit(struct buf *buf, struct request *rq, struct bio *bio)
{
	memset(buf, 0, sizeof(*buf));
	buf->rq = rq;
	buf->bio = bio;
	buf->iter = bio->bi_iter;
}