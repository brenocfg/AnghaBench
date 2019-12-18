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
struct videobuf_queue {struct cx231xx_fh* priv_data; } ;
struct cx231xx_fh {TYPE_2__* dev; } ;
struct TYPE_3__ {unsigned int ts_packet_size; unsigned int ts_packet_count; } ;
struct TYPE_4__ {TYPE_1__ ts1; } ;

/* Variables and functions */
 unsigned int mpegbufs ; 
 unsigned int mpeglines ; 
 unsigned int mpeglinesize ; 

__attribute__((used)) static int bb_buf_setup(struct videobuf_queue *q,
	unsigned int *count, unsigned int *size)
{
	struct cx231xx_fh *fh = q->priv_data;

	fh->dev->ts1.ts_packet_size  = mpeglinesize;
	fh->dev->ts1.ts_packet_count = mpeglines;

	*size = fh->dev->ts1.ts_packet_size * fh->dev->ts1.ts_packet_count;
	*count = mpegbufs;

	return 0;
}