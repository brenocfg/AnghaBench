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
typedef  unsigned int u32 ;
struct ocotp_priv {int /*<<< orphan*/  clk; scalar_t__ base; int /*<<< orphan*/  dev; TYPE_1__* params; } ;
struct TYPE_2__ {unsigned int nregs; } ;

/* Variables and functions */
 scalar_t__ IMX_OCOTP_OFFSET_B0W0 ; 
 int IMX_OCOTP_OFFSET_PER_WORD ; 
 unsigned int IMX_OCOTP_READ_LOCKED_VAL ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  imx_ocotp_clr_err_if_set (scalar_t__) ; 
 int imx_ocotp_wait_for_busy (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocotp_mutex ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 

__attribute__((used)) static int imx_ocotp_read(void *context, unsigned int offset,
			  void *val, size_t bytes)
{
	struct ocotp_priv *priv = context;
	unsigned int count;
	u32 *buf = val;
	int i, ret;
	u32 index;

	index = offset >> 2;
	count = bytes >> 2;

	if (count > (priv->params->nregs - index))
		count = priv->params->nregs - index;

	mutex_lock(&ocotp_mutex);

	ret = clk_prepare_enable(priv->clk);
	if (ret < 0) {
		mutex_unlock(&ocotp_mutex);
		dev_err(priv->dev, "failed to prepare/enable ocotp clk\n");
		return ret;
	}

	ret = imx_ocotp_wait_for_busy(priv->base, 0);
	if (ret < 0) {
		dev_err(priv->dev, "timeout during read setup\n");
		goto read_end;
	}

	for (i = index; i < (index + count); i++) {
		*buf++ = readl(priv->base + IMX_OCOTP_OFFSET_B0W0 +
			       i * IMX_OCOTP_OFFSET_PER_WORD);

		/* 47.3.1.2
		 * For "read locked" registers 0xBADABADA will be returned and
		 * HW_OCOTP_CTRL[ERROR] will be set. It must be cleared by
		 * software before any new write, read or reload access can be
		 * issued
		 */
		if (*(buf - 1) == IMX_OCOTP_READ_LOCKED_VAL)
			imx_ocotp_clr_err_if_set(priv->base);
	}
	ret = 0;

read_end:
	clk_disable_unprepare(priv->clk);
	mutex_unlock(&ocotp_mutex);
	return ret;
}