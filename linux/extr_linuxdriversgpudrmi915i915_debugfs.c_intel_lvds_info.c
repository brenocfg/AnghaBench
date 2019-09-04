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
struct intel_connector {int /*<<< orphan*/  panel; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_panel_info (struct seq_file*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void intel_lvds_info(struct seq_file *m,
			    struct intel_connector *intel_connector)
{
	intel_panel_info(m, &intel_connector->panel);
}