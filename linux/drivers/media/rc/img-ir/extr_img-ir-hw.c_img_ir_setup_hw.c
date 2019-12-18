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
struct TYPE_2__ {int /*<<< orphan*/  rdev; } ;
struct img_ir_priv {TYPE_1__ hw; } ;
struct img_ir_decoder {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 scalar_t__ img_ir_decoder_compatible (struct img_ir_priv*,struct img_ir_decoder const*) ; 
 struct img_ir_decoder** img_ir_decoders ; 
 int /*<<< orphan*/  img_ir_set_decoder (struct img_ir_priv*,struct img_ir_decoder const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  img_ir_set_protocol (struct img_ir_priv*,int /*<<< orphan*/ ) ; 

void img_ir_setup_hw(struct img_ir_priv *priv)
{
	struct img_ir_decoder **decp;

	if (!priv->hw.rdev)
		return;

	/* Use the first available decoder (or disable stuff if NULL) */
	for (decp = img_ir_decoders; *decp; ++decp) {
		const struct img_ir_decoder *dec = *decp;
		if (img_ir_decoder_compatible(priv, dec)) {
			img_ir_set_protocol(priv, dec->type);
			img_ir_set_decoder(priv, dec, 0);
			return;
		}
	}
	img_ir_set_decoder(priv, NULL, 0);
}