#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  verifier_state_t ;
typedef  int uint32_t ;
struct TYPE_4__ {int** fire_offsets; int num_fire_offsets; } ;
typedef  TYPE_1__ drm_via_private_t ;

/* Variables and functions */
 int const HALCYON_FIRECMD ; 
 int const HALCYON_FIREMASK ; 
 int const HALCYON_HEADER1 ; 
 int const HALCYON_HEADER1MASK ; 
 int const HC_ACMD_HCmdB ; 
 int const HC_ACMD_MASK ; 
 int const HC_HEADER2 ; 
#define  HC_ParaType_CmdVdata 128 
 scalar_t__ HC_REG_BASE ; 
 scalar_t__ HC_REG_TRANS_SET ; 
 scalar_t__ HC_REG_TRANS_SPACE ; 
 int const VIA_VIDEOMASK ; 
 int const VIA_VIDEO_HEADER5 ; 
 int const VIA_VIDEO_HEADER6 ; 
 int /*<<< orphan*/  state_command ; 
 int /*<<< orphan*/  via_write (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline__ verifier_state_t
via_parse_header2(drm_via_private_t *dev_priv, uint32_t const **buffer,
		  const uint32_t *buf_end, int *fire_count)
{
	uint32_t cmd;
	const uint32_t *buf = *buffer;
	const uint32_t *next_fire;
	int burst = 0;

	next_fire = dev_priv->fire_offsets[*fire_count];
	buf++;
	cmd = (*buf & 0xFFFF0000) >> 16;
	via_write(dev_priv, HC_REG_TRANS_SET + HC_REG_BASE, *buf++);
	switch (cmd) {
	case HC_ParaType_CmdVdata:
		while ((buf < buf_end) &&
		       (*fire_count < dev_priv->num_fire_offsets) &&
		       (*buf & HC_ACMD_MASK) == HC_ACMD_HCmdB) {
			while (buf <= next_fire) {
				via_write(dev_priv, HC_REG_TRANS_SPACE + HC_REG_BASE +
					  (burst & 63), *buf++);
				burst += 4;
			}
			if ((buf < buf_end)
			    && ((*buf & HALCYON_FIREMASK) == HALCYON_FIRECMD))
				buf++;

			if (++(*fire_count) < dev_priv->num_fire_offsets)
				next_fire = dev_priv->fire_offsets[*fire_count];
		}
		break;
	default:
		while (buf < buf_end) {

			if (*buf == HC_HEADER2 ||
			    (*buf & HALCYON_HEADER1MASK) == HALCYON_HEADER1 ||
			    (*buf & VIA_VIDEOMASK) == VIA_VIDEO_HEADER5 ||
			    (*buf & VIA_VIDEOMASK) == VIA_VIDEO_HEADER6)
				break;

			via_write(dev_priv, HC_REG_TRANS_SPACE + HC_REG_BASE +
				  (burst & 63), *buf++);
			burst += 4;
		}
	}
	*buffer = buf;
	return state_command;
}