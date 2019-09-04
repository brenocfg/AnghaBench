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
typedef  int /*<<< orphan*/  u32 ;
struct hva_enc {int (* open ) (struct hva_ctx*) ;int /*<<< orphan*/  name; } ;
struct hva_dev {int instance_id; } ;
struct hva_ctx {int /*<<< orphan*/  name; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct device* ctx_to_dev (struct hva_ctx*) ; 
 struct hva_dev* ctx_to_hdev (struct hva_ctx*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ hva_find_encoder (struct hva_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,char*) ; 
 int stub1 (struct hva_ctx*) ; 

__attribute__((used)) static int hva_open_encoder(struct hva_ctx *ctx, u32 streamformat,
			    u32 pixelformat, struct hva_enc **penc)
{
	struct hva_dev *hva = ctx_to_hdev(ctx);
	struct device *dev = ctx_to_dev(ctx);
	struct hva_enc *enc;
	int ret;

	/* find an encoder which can deal with these formats */
	enc = (struct hva_enc *)hva_find_encoder(ctx, pixelformat,
						 streamformat);
	if (!enc) {
		dev_err(dev, "%s no encoder found matching %4.4s => %4.4s\n",
			ctx->name, (char *)&pixelformat, (char *)&streamformat);
		return -EINVAL;
	}

	dev_dbg(dev, "%s one encoder matching %4.4s => %4.4s\n",
		ctx->name, (char *)&pixelformat, (char *)&streamformat);

	/* update instance name */
	snprintf(ctx->name, sizeof(ctx->name), "[%3d:%4.4s]",
		 hva->instance_id, (char *)&streamformat);

	/* open encoder instance */
	ret = enc->open(ctx);
	if (ret) {
		dev_err(dev, "%s failed to open encoder instance (%d)\n",
			ctx->name, ret);
		return ret;
	}

	dev_dbg(dev, "%s %s encoder opened\n", ctx->name, enc->name);

	*penc = enc;

	return ret;
}