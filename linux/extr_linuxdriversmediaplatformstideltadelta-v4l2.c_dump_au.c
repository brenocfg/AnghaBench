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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct delta_dev {int /*<<< orphan*/  dev; } ;
struct delta_ctx {int /*<<< orphan*/  name; struct delta_dev* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  index; } ;
struct TYPE_4__ {TYPE_1__ vb2_buf; } ;
struct delta_au {int size; int /*<<< orphan*/  dts; TYPE_2__ vbuf; scalar_t__ vaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,...) ; 

__attribute__((used)) static void dump_au(struct delta_ctx *ctx, struct delta_au *au)
{
	struct delta_dev *delta = ctx->dev;
	u32 size = 10;	/* dump first & last 10 bytes */
	u8 *data = (u8 *)(au->vaddr);

	if (au->size <= (size * 2))
		dev_dbg(delta->dev, "%s dump au[%d] dts=%lld size=%d data=%*ph\n",
			ctx->name, au->vbuf.vb2_buf.index, au->dts, au->size,
			au->size, data);
	else
		dev_dbg(delta->dev, "%s dump au[%d] dts=%lld size=%d data=%*ph..%*ph\n",
			ctx->name, au->vbuf.vb2_buf.index, au->dts, au->size,
			size, data, size, data + au->size - size);
}