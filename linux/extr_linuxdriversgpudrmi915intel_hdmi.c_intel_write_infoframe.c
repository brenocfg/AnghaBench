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
struct TYPE_2__ {int /*<<< orphan*/  type; } ;
union hdmi_infoframe {TYPE_1__ any; } ;
typedef  scalar_t__ u8 ;
struct intel_digital_port {int /*<<< orphan*/  (* write_infoframe ) (struct drm_encoder*,struct intel_crtc_state const*,int /*<<< orphan*/ ,scalar_t__*,scalar_t__) ;} ;
struct intel_crtc_state {int dummy; } ;
struct drm_encoder {int dummy; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int VIDEO_DIP_DATA_SIZE ; 
 struct intel_digital_port* enc_to_dig_port (struct drm_encoder*) ; 
 scalar_t__ hdmi_infoframe_pack (union hdmi_infoframe*,scalar_t__*,int) ; 
 int /*<<< orphan*/  stub1 (struct drm_encoder*,struct intel_crtc_state const*,int /*<<< orphan*/ ,scalar_t__*,scalar_t__) ; 

__attribute__((used)) static void intel_write_infoframe(struct drm_encoder *encoder,
				  const struct intel_crtc_state *crtc_state,
				  union hdmi_infoframe *frame)
{
	struct intel_digital_port *intel_dig_port = enc_to_dig_port(encoder);
	u8 buffer[VIDEO_DIP_DATA_SIZE];
	ssize_t len;

	/* see comment above for the reason for this offset */
	len = hdmi_infoframe_pack(frame, buffer + 1, sizeof(buffer) - 1);
	if (len < 0)
		return;

	/* Insert the 'hole' (see big comment above) at position 3 */
	buffer[0] = buffer[1];
	buffer[1] = buffer[2];
	buffer[2] = buffer[3];
	buffer[3] = 0;
	len++;

	intel_dig_port->write_infoframe(encoder, crtc_state, frame->any.type, buffer, len);
}