#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct seq_file {int dummy; } ;
struct intel_hdmi {int /*<<< orphan*/  has_audio; } ;
struct intel_encoder {int /*<<< orphan*/  base; } ;
struct intel_connector {struct intel_encoder* encoder; } ;

/* Variables and functions */
 struct intel_hdmi* enc_to_intel_hdmi (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yesno (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_hdmi_info(struct seq_file *m,
			    struct intel_connector *intel_connector)
{
	struct intel_encoder *intel_encoder = intel_connector->encoder;
	struct intel_hdmi *intel_hdmi = enc_to_intel_hdmi(&intel_encoder->base);

	seq_printf(m, "\taudio support: %s\n", yesno(intel_hdmi->has_audio));
}