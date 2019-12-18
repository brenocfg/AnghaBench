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
struct seq_file {struct dwc2_hsotg* private; } ;
struct dwc2_hsotg {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_property_read_string (int /*<<< orphan*/ ,char*,char const**) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char const*) ; 

__attribute__((used)) static int dr_mode_show(struct seq_file *seq, void *v)
{
	struct dwc2_hsotg *hsotg = seq->private;
	const char *dr_mode = "";

	device_property_read_string(hsotg->dev, "dr_mode", &dr_mode);
	seq_printf(seq, "%s\n", dr_mode);
	return 0;
}