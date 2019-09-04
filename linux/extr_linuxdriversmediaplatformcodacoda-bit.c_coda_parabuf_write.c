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
typedef  int /*<<< orphan*/  u32 ;
struct coda_dev {TYPE_2__* devtype; } ;
struct TYPE_3__ {int /*<<< orphan*/ * vaddr; } ;
struct coda_ctx {TYPE_1__ parabuf; struct coda_dev* dev; } ;
struct TYPE_4__ {scalar_t__ product; } ;

/* Variables and functions */
 scalar_t__ CODA_DX6 ; 

__attribute__((used)) static void coda_parabuf_write(struct coda_ctx *ctx, int index, u32 value)
{
	struct coda_dev *dev = ctx->dev;
	u32 *p = ctx->parabuf.vaddr;

	if (dev->devtype->product == CODA_DX6)
		p[index] = value;
	else
		p[index ^ 1] = value;
}