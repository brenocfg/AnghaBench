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
typedef  int u32 ;
struct seq_file {struct asus_wmi* private; } ;
struct TYPE_2__ {int /*<<< orphan*/  ctrl_param; int /*<<< orphan*/  dev_id; } ;
struct asus_wmi {TYPE_1__ debug; } ;

/* Variables and functions */
 int asus_wmi_set_devstate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int show_devs(struct seq_file *m, void *data)
{
	struct asus_wmi *asus = m->private;
	int err;
	u32 retval = -1;

	err = asus_wmi_set_devstate(asus->debug.dev_id, asus->debug.ctrl_param,
				    &retval);
	if (err < 0)
		return err;

	seq_printf(m, "DEVS(%#x, %#x) = %#x\n", asus->debug.dev_id,
		   asus->debug.ctrl_param, retval);

	return 0;
}