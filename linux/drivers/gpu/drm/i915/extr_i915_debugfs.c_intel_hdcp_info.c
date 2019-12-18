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
struct intel_connector {int dummy; } ;

/* Variables and functions */
 int intel_hdcp2_capable (struct intel_connector*) ; 
 int intel_hdcp_capable (struct intel_connector*) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static void intel_hdcp_info(struct seq_file *m,
			    struct intel_connector *intel_connector)
{
	bool hdcp_cap, hdcp2_cap;

	hdcp_cap = intel_hdcp_capable(intel_connector);
	hdcp2_cap = intel_hdcp2_capable(intel_connector);

	if (hdcp_cap)
		seq_puts(m, "HDCP1.4 ");
	if (hdcp2_cap)
		seq_puts(m, "HDCP2.2 ");

	if (!hdcp_cap && !hdcp2_cap)
		seq_puts(m, "None");

	seq_puts(m, "\n");
}