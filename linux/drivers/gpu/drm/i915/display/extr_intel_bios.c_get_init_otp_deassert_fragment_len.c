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
typedef  int u8 ;
struct TYPE_3__ {int** sequence; int seq_version; } ;
struct TYPE_4__ {TYPE_1__ dsi; } ;
struct drm_i915_private {TYPE_2__ vbt; } ;

/* Variables and functions */
#define  MIPI_SEQ_ELEM_DELAY 130 
 int const MIPI_SEQ_ELEM_END ; 
#define  MIPI_SEQ_ELEM_GPIO 129 
#define  MIPI_SEQ_ELEM_SEND_PKT 128 
 size_t MIPI_SEQ_INIT_OTP ; 
 scalar_t__ WARN_ON (int) ; 

__attribute__((used)) static int get_init_otp_deassert_fragment_len(struct drm_i915_private *dev_priv)
{
	const u8 *data = dev_priv->vbt.dsi.sequence[MIPI_SEQ_INIT_OTP];
	int index, len;

	if (WARN_ON(!data || dev_priv->vbt.dsi.seq_version != 1))
		return 0;

	/* index = 1 to skip sequence byte */
	for (index = 1; data[index] != MIPI_SEQ_ELEM_END; index += len) {
		switch (data[index]) {
		case MIPI_SEQ_ELEM_SEND_PKT:
			return index == 1 ? 0 : index;
		case MIPI_SEQ_ELEM_DELAY:
			len = 5; /* 1 byte for operand + uint32 */
			break;
		case MIPI_SEQ_ELEM_GPIO:
			len = 3; /* 1 byte for op, 1 for gpio_nr, 1 for value */
			break;
		default:
			return 0;
		}
	}

	return 0;
}