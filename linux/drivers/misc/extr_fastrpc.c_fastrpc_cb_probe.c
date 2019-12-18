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
struct device {int /*<<< orphan*/  of_node; int /*<<< orphan*/  parent; } ;
struct platform_device {struct device dev; } ;
struct fastrpc_session_ctx {int used; int valid; int sid; struct device* dev; } ;
struct fastrpc_channel_ctx {size_t sesscount; int /*<<< orphan*/  lock; struct fastrpc_session_ctx* session; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  FASTRPC_MAX_SESSIONS ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct fastrpc_channel_ctx* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct fastrpc_session_ctx*) ; 
 int dma_set_mask (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct fastrpc_session_ctx*,struct fastrpc_session_ctx*,int) ; 
 scalar_t__ of_property_read_u32 (int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int fastrpc_cb_probe(struct platform_device *pdev)
{
	struct fastrpc_channel_ctx *cctx;
	struct fastrpc_session_ctx *sess;
	struct device *dev = &pdev->dev;
	int i, sessions = 0;
	unsigned long flags;
	int rc;

	cctx = dev_get_drvdata(dev->parent);
	if (!cctx)
		return -EINVAL;

	of_property_read_u32(dev->of_node, "qcom,nsessions", &sessions);

	spin_lock_irqsave(&cctx->lock, flags);
	sess = &cctx->session[cctx->sesscount];
	sess->used = false;
	sess->valid = true;
	sess->dev = dev;
	dev_set_drvdata(dev, sess);

	if (of_property_read_u32(dev->of_node, "reg", &sess->sid))
		dev_info(dev, "FastRPC Session ID not specified in DT\n");

	if (sessions > 0) {
		struct fastrpc_session_ctx *dup_sess;

		for (i = 1; i < sessions; i++) {
			if (cctx->sesscount++ >= FASTRPC_MAX_SESSIONS)
				break;
			dup_sess = &cctx->session[cctx->sesscount];
			memcpy(dup_sess, sess, sizeof(*dup_sess));
		}
	}
	cctx->sesscount++;
	spin_unlock_irqrestore(&cctx->lock, flags);
	rc = dma_set_mask(dev, DMA_BIT_MASK(32));
	if (rc) {
		dev_err(dev, "32-bit DMA enable failed\n");
		return rc;
	}

	return 0;
}