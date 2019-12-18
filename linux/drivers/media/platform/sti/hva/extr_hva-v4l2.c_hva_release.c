#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hva_enc {int /*<<< orphan*/  (* close ) (struct hva_ctx*) ;int /*<<< orphan*/  name; } ;
struct hva_dev {int /*<<< orphan*/  nb_of_instances; int /*<<< orphan*/ ** instances; } ;
struct TYPE_3__ {int /*<<< orphan*/  m2m_ctx; } ;
struct hva_ctx {size_t id; int /*<<< orphan*/  name; TYPE_1__ fh; int /*<<< orphan*/  ctrl_handler; struct hva_enc* enc; } ;
struct file {int /*<<< orphan*/  private_data; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct device* ctx_to_dev (struct hva_ctx*) ; 
 struct hva_dev* ctx_to_hdev (struct hva_ctx*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct hva_ctx* fh_to_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hva_dbg_ctx_remove (struct hva_ctx*) ; 
 int /*<<< orphan*/  hva_dbg_summary (struct hva_ctx*) ; 
 int /*<<< orphan*/  kfree (struct hva_ctx*) ; 
 int /*<<< orphan*/  stub1 (struct hva_ctx*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_fh_del (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_fh_exit (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_m2m_ctx_release (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hva_release(struct file *file)
{
	struct hva_ctx *ctx = fh_to_ctx(file->private_data);
	struct hva_dev *hva = ctx_to_hdev(ctx);
	struct device *dev = ctx_to_dev(ctx);
	const struct hva_enc *enc = ctx->enc;

	if (enc) {
		dev_dbg(dev, "%s %s encoder closed\n", ctx->name, enc->name);
		enc->close(ctx);
		ctx->enc = NULL;

		/* clear instance context in instances array */
		hva->instances[ctx->id] = NULL;
		hva->nb_of_instances--;
	}

	/* trace a summary of instance before closing (debug purpose) */
	hva_dbg_summary(ctx);

	v4l2_m2m_ctx_release(ctx->fh.m2m_ctx);

	v4l2_ctrl_handler_free(&ctx->ctrl_handler);

	v4l2_fh_del(&ctx->fh);
	v4l2_fh_exit(&ctx->fh);

#ifdef CONFIG_VIDEO_STI_HVA_DEBUGFS
	hva_dbg_ctx_remove(ctx);
#endif

	dev_info(dev, "%s encoder instance released\n", ctx->name);

	kfree(ctx);

	return 0;
}