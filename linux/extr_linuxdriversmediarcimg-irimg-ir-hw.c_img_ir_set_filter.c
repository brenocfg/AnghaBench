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
struct rc_scancode_filter {unsigned long long data; unsigned long long mask; } ;
struct rc_dev {unsigned long long enabled_protocols; unsigned long long wakeup_protocol; struct img_ir_priv* priv; } ;
struct img_ir_priv_hw {TYPE_1__* decoder; } ;
struct img_ir_priv {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; struct img_ir_priv_hw hw; } ;
struct img_ir_filter {scalar_t__ mask; scalar_t__ data; int /*<<< orphan*/  maxlen; scalar_t__ minlen; } ;
typedef  enum rc_filter_type { ____Placeholder_rc_filter_type } rc_filter_type ;
struct TYPE_2__ {int (* filter ) (struct rc_scancode_filter*,struct img_ir_filter*,unsigned long long) ;} ;

/* Variables and functions */
 int EINVAL ; 
#define  RC_FILTER_NORMAL 129 
#define  RC_FILTER_WAKEUP 128 
 int /*<<< orphan*/  _img_ir_set_filter (struct img_ir_priv*,struct img_ir_filter*) ; 
 int /*<<< orphan*/  _img_ir_set_wake_filter (struct img_ir_priv*,struct img_ir_filter*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char*,unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int stub1 (struct rc_scancode_filter*,struct img_ir_filter*,unsigned long long) ; 
 int stub2 (struct rc_scancode_filter*,struct img_ir_filter*,unsigned long long) ; 

__attribute__((used)) static int img_ir_set_filter(struct rc_dev *dev, enum rc_filter_type type,
			     struct rc_scancode_filter *sc_filter)
{
	struct img_ir_priv *priv = dev->priv;
	struct img_ir_priv_hw *hw = &priv->hw;
	struct img_ir_filter filter, *filter_ptr = &filter;
	int ret = 0;

	dev_dbg(priv->dev, "IR scancode %sfilter=%08x & %08x\n",
		type == RC_FILTER_WAKEUP ? "wake " : "",
		sc_filter->data,
		sc_filter->mask);

	spin_lock_irq(&priv->lock);

	/* filtering can always be disabled */
	if (!sc_filter->mask) {
		filter_ptr = NULL;
		goto set_unlock;
	}

	/* current decoder must support scancode filtering */
	if (!hw->decoder || !hw->decoder->filter) {
		ret = -EINVAL;
		goto unlock;
	}

	/* convert scancode filter to raw filter */
	filter.minlen = 0;
	filter.maxlen = ~0;
	if (type == RC_FILTER_NORMAL) {
		/* guess scancode from protocol */
		ret = hw->decoder->filter(sc_filter, &filter,
					  dev->enabled_protocols);
	} else {
		/* for wakeup user provided exact protocol variant */
		ret = hw->decoder->filter(sc_filter, &filter,
					  1ULL << dev->wakeup_protocol);
	}
	if (ret)
		goto unlock;
	dev_dbg(priv->dev, "IR raw %sfilter=%016llx & %016llx\n",
		type == RC_FILTER_WAKEUP ? "wake " : "",
		(unsigned long long)filter.data,
		(unsigned long long)filter.mask);

set_unlock:
	/* apply raw filters */
	switch (type) {
	case RC_FILTER_NORMAL:
		_img_ir_set_filter(priv, filter_ptr);
		break;
	case RC_FILTER_WAKEUP:
		_img_ir_set_wake_filter(priv, filter_ptr);
		break;
	default:
		ret = -EINVAL;
	}

unlock:
	spin_unlock_irq(&priv->lock);
	return ret;
}