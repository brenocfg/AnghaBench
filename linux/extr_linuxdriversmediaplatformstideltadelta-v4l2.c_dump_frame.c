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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct delta_frame {int /*<<< orphan*/  field; int /*<<< orphan*/  flags; int /*<<< orphan*/  dts; int /*<<< orphan*/  index; scalar_t__ vaddr; } ;
struct delta_dev {int /*<<< orphan*/  dev; } ;
struct delta_ctx {int /*<<< orphan*/  name; struct delta_dev* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  frame_field_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frame_type_str (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dump_frame(struct delta_ctx *ctx, struct delta_frame *frame)
{
	struct delta_dev *delta = ctx->dev;
	u32 size = 10;	/* dump first 10 bytes */
	u8 *data = (u8 *)(frame->vaddr);

	dev_dbg(delta->dev, "%s dump frame[%d] dts=%lld type=%s field=%s data=%*ph\n",
		ctx->name, frame->index, frame->dts,
		frame_type_str(frame->flags),
		frame_field_str(frame->field),
		size, data);
}