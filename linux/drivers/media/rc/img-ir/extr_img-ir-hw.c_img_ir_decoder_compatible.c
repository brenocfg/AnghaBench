#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* ct_quirks; } ;
struct img_ir_priv {TYPE_2__ hw; } ;
struct TYPE_3__ {unsigned int code_type; } ;
struct img_ir_decoder {TYPE_1__ control; } ;

/* Variables and functions */
 int IMG_IR_QUIRK_CODE_BROKEN ; 

__attribute__((used)) static bool img_ir_decoder_compatible(struct img_ir_priv *priv,
				      const struct img_ir_decoder *dec)
{
	unsigned int ct;

	/* don't accept decoders using code types which aren't supported */
	ct = dec->control.code_type;
	if (priv->hw.ct_quirks[ct] & IMG_IR_QUIRK_CODE_BROKEN)
		return false;

	return true;
}