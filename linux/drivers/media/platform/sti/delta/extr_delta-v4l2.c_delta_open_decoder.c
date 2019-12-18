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
typedef  int /*<<< orphan*/  u32 ;
struct delta_dev {int instance_id; int /*<<< orphan*/  dev; } ;
struct delta_dec {int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  pixelformat; } ;
struct delta_ctx {int /*<<< orphan*/  name; TYPE_1__ frameinfo; struct delta_dev* dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int call_dec_op (struct delta_dec const*,int /*<<< orphan*/ ,struct delta_ctx*) ; 
 struct delta_dec* delta_find_decoder (struct delta_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  open ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,char*) ; 

__attribute__((used)) static int delta_open_decoder(struct delta_ctx *ctx, u32 streamformat,
			      u32 pixelformat, const struct delta_dec **pdec)
{
	struct delta_dev *delta = ctx->dev;
	const struct delta_dec *dec;
	int ret;

	dec = delta_find_decoder(ctx, streamformat, ctx->frameinfo.pixelformat);
	if (!dec) {
		dev_err(delta->dev, "%s no decoder found matching %4.4s => %4.4s\n",
			ctx->name, (char *)&streamformat, (char *)&pixelformat);
		return -EINVAL;
	}

	dev_dbg(delta->dev, "%s one decoder matching %4.4s => %4.4s\n",
		ctx->name, (char *)&streamformat, (char *)&pixelformat);

	/* update instance name */
	snprintf(ctx->name, sizeof(ctx->name), "[%3d:%4.4s]",
		 delta->instance_id, (char *)&streamformat);

	/* open decoder instance */
	ret = call_dec_op(dec, open, ctx);
	if (ret) {
		dev_err(delta->dev, "%s failed to open decoder instance (%d)\n",
			ctx->name, ret);
		return ret;
	}

	dev_dbg(delta->dev, "%s %s decoder opened\n", ctx->name, dec->name);

	*pdec = dec;

	return ret;
}