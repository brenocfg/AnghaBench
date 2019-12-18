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
typedef  int u32 ;
struct ipu_ic_priv {int /*<<< orphan*/  lock; } ;
struct ipu_ic_csc {int /*<<< orphan*/  out_cs; int /*<<< orphan*/  in_cs; } ;
struct ipu_ic {int /*<<< orphan*/  out_cs; int /*<<< orphan*/  in_cs; TYPE_1__* reg; struct ipu_ic_priv* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  rsc; } ;

/* Variables and functions */
 int calc_resize_coeffs (struct ipu_ic*,int,int,int*,int*) ; 
 int init_csc (struct ipu_ic*,struct ipu_ic_csc const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_ic_write (struct ipu_ic*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int ipu_ic_task_init_rsc(struct ipu_ic *ic,
			 const struct ipu_ic_csc *csc,
			 int in_width, int in_height,
			 int out_width, int out_height,
			 u32 rsc)
{
	struct ipu_ic_priv *priv = ic->priv;
	u32 downsize_coeff, resize_coeff;
	unsigned long flags;
	int ret = 0;

	if (!rsc) {
		/* Setup vertical resizing */

		ret = calc_resize_coeffs(ic, in_height, out_height,
					 &resize_coeff, &downsize_coeff);
		if (ret)
			return ret;

		rsc = (downsize_coeff << 30) | (resize_coeff << 16);

		/* Setup horizontal resizing */
		ret = calc_resize_coeffs(ic, in_width, out_width,
					 &resize_coeff, &downsize_coeff);
		if (ret)
			return ret;

		rsc |= (downsize_coeff << 14) | resize_coeff;
	}

	spin_lock_irqsave(&priv->lock, flags);

	ipu_ic_write(ic, rsc, ic->reg->rsc);

	/* Setup color space conversion */
	ic->in_cs = csc->in_cs;
	ic->out_cs = csc->out_cs;

	ret = init_csc(ic, csc, 0);

	spin_unlock_irqrestore(&priv->lock, flags);
	return ret;
}