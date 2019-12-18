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
struct seq_file {int dummy; } ;
struct intel_hdmi {int /*<<< orphan*/  has_audio; } ;
struct intel_encoder {int /*<<< orphan*/  base; } ;
struct TYPE_2__ {scalar_t__ shim; } ;
struct intel_connector {TYPE_1__ hdcp; struct intel_encoder* encoder; } ;

/* Variables and functions */
 struct intel_hdmi* enc_to_intel_hdmi (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_hdcp_info (struct seq_file*,struct intel_connector*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 int /*<<< orphan*/  yesno (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_hdmi_info(struct seq_file *m,
			    struct intel_connector *intel_connector)
{
	struct intel_encoder *intel_encoder = intel_connector->encoder;
	struct intel_hdmi *intel_hdmi = enc_to_intel_hdmi(&intel_encoder->base);

	seq_printf(m, "\taudio support: %s\n", yesno(intel_hdmi->has_audio));
	if (intel_connector->hdcp.shim) {
		seq_puts(m, "\tHDCP version: ");
		intel_hdcp_info(m, intel_connector);
	}
}