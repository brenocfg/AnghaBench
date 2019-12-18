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
struct TYPE_4__ {int type; } ;
union hdmi_infoframe {TYPE_2__ any; } ;
typedef  scalar_t__ u8 ;
struct intel_encoder {int /*<<< orphan*/  base; } ;
struct intel_digital_port {int /*<<< orphan*/  (* write_infoframe ) (struct intel_encoder*,struct intel_crtc_state const*,int,scalar_t__*,scalar_t__) ;} ;
struct TYPE_3__ {int enable; } ;
struct intel_crtc_state {TYPE_1__ infoframes; } ;
typedef  scalar_t__ ssize_t ;
typedef  enum hdmi_infoframe_type { ____Placeholder_hdmi_infoframe_type } hdmi_infoframe_type ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int VIDEO_DIP_DATA_SIZE ; 
 scalar_t__ WARN_ON (int) ; 
 struct intel_digital_port* enc_to_dig_port (int /*<<< orphan*/ *) ; 
 scalar_t__ hdmi_infoframe_pack_only (union hdmi_infoframe const*,scalar_t__*,int) ; 
 int intel_hdmi_infoframe_enable (int) ; 
 int /*<<< orphan*/  memmove (scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  stub1 (struct intel_encoder*,struct intel_crtc_state const*,int,scalar_t__*,scalar_t__) ; 

__attribute__((used)) static void intel_write_infoframe(struct intel_encoder *encoder,
				  const struct intel_crtc_state *crtc_state,
				  enum hdmi_infoframe_type type,
				  const union hdmi_infoframe *frame)
{
	struct intel_digital_port *intel_dig_port = enc_to_dig_port(&encoder->base);
	u8 buffer[VIDEO_DIP_DATA_SIZE];
	ssize_t len;

	if ((crtc_state->infoframes.enable &
	     intel_hdmi_infoframe_enable(type)) == 0)
		return;

	if (WARN_ON(frame->any.type != type))
		return;

	/* see comment above for the reason for this offset */
	len = hdmi_infoframe_pack_only(frame, buffer + 1, sizeof(buffer) - 1);
	if (WARN_ON(len < 0))
		return;

	/* Insert the 'hole' (see big comment above) at position 3 */
	memmove(&buffer[0], &buffer[1], 3);
	buffer[3] = 0;
	len++;

	intel_dig_port->write_infoframe(encoder, crtc_state, type, buffer, len);
}