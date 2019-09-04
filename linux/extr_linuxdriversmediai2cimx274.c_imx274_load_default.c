#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_3__* vflip; TYPE_3__* gain; TYPE_3__* exposure; TYPE_1__* test_pattern; } ;
struct TYPE_8__ {int numerator; int denominator; } ;
struct stimx274 {TYPE_2__ ctrls; TYPE_4__ frame_interval; } ;
struct TYPE_7__ {int val; } ;
struct TYPE_5__ {int /*<<< orphan*/  val; } ;

/* Variables and functions */
 int IMX274_DEF_FRAME_RATE ; 
 int IMX274_DEF_GAIN ; 
 int /*<<< orphan*/  TEST_PATTERN_DISABLED ; 
 int imx274_set_frame_interval (struct stimx274*,TYPE_4__) ; 
 int v4l2_ctrl_s_ctrl (TYPE_3__*,int) ; 

__attribute__((used)) static int imx274_load_default(struct stimx274 *priv)
{
	int ret;

	/* load default control values */
	priv->frame_interval.numerator = 1;
	priv->frame_interval.denominator = IMX274_DEF_FRAME_RATE;
	priv->ctrls.exposure->val = 1000000 / IMX274_DEF_FRAME_RATE;
	priv->ctrls.gain->val = IMX274_DEF_GAIN;
	priv->ctrls.vflip->val = 0;
	priv->ctrls.test_pattern->val = TEST_PATTERN_DISABLED;

	/* update frame rate */
	ret = imx274_set_frame_interval(priv,
					priv->frame_interval);
	if (ret)
		return ret;

	/* update exposure time */
	ret = v4l2_ctrl_s_ctrl(priv->ctrls.exposure, priv->ctrls.exposure->val);
	if (ret)
		return ret;

	/* update gain */
	ret = v4l2_ctrl_s_ctrl(priv->ctrls.gain, priv->ctrls.gain->val);
	if (ret)
		return ret;

	/* update vflip */
	ret = v4l2_ctrl_s_ctrl(priv->ctrls.vflip, priv->ctrls.vflip->val);
	if (ret)
		return ret;

	return 0;
}