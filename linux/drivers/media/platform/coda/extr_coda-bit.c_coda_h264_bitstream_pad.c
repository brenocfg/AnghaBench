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
typedef  int u32 ;
struct coda_ctx {int /*<<< orphan*/  bitstream_fifo; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  coda_h264_filler_nal (int,unsigned char*) ; 
 int kfifo_in (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int coda_h264_bitstream_pad(struct coda_ctx *ctx, u32 size)
{
	unsigned char *buf;
	u32 n;

	if (size < 6)
		size = 6;

	buf = kmalloc(size, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	coda_h264_filler_nal(size, buf);
	n = kfifo_in(&ctx->bitstream_fifo, buf, size);
	kfree(buf);

	return (n < size) ? -ENOSPC : 0;
}