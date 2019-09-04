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
typedef  int u64 ;
struct rc_dev {int allowed_wakeup_protocols; struct img_ir_priv* priv; } ;
struct img_ir_priv_hw {TYPE_1__* decoder; struct rc_dev* rdev; } ;
struct img_ir_priv {struct img_ir_priv_hw hw; } ;
struct img_ir_decoder {int type; } ;
struct TYPE_2__ {int /*<<< orphan*/  filter; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  img_ir_decoder_compatible (struct img_ir_priv*,struct img_ir_decoder const*) ; 
 struct img_ir_decoder** img_ir_decoders ; 
 int /*<<< orphan*/  img_ir_set_decoder (struct img_ir_priv*,struct img_ir_decoder const*,int) ; 

__attribute__((used)) static int img_ir_change_protocol(struct rc_dev *dev, u64 *ir_type)
{
	struct img_ir_priv *priv = dev->priv;
	struct img_ir_priv_hw *hw = &priv->hw;
	struct rc_dev *rdev = hw->rdev;
	struct img_ir_decoder **decp;
	u64 wakeup_protocols;

	if (!*ir_type) {
		/* disable all protocols */
		img_ir_set_decoder(priv, NULL, 0);
		goto success;
	}
	for (decp = img_ir_decoders; *decp; ++decp) {
		const struct img_ir_decoder *dec = *decp;
		if (!img_ir_decoder_compatible(priv, dec))
			continue;
		if (*ir_type & dec->type) {
			*ir_type &= dec->type;
			img_ir_set_decoder(priv, dec, *ir_type);
			goto success;
		}
	}
	return -EINVAL;

success:
	/*
	 * Only allow matching wakeup protocols for now, and only if filtering
	 * is supported.
	 */
	wakeup_protocols = *ir_type;
	if (!hw->decoder || !hw->decoder->filter)
		wakeup_protocols = 0;
	rdev->allowed_wakeup_protocols = wakeup_protocols;
	return 0;
}