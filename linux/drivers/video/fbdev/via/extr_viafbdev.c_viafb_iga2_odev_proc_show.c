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
struct seq_file {int dummy; } ;
struct TYPE_4__ {TYPE_1__* shared; } ;
struct TYPE_3__ {int /*<<< orphan*/  iga2_devices; } ;

/* Variables and functions */
 int /*<<< orphan*/  via_odev_to_seq (struct seq_file*,int /*<<< orphan*/ ) ; 
 TYPE_2__* viaparinfo ; 

__attribute__((used)) static int viafb_iga2_odev_proc_show(struct seq_file *m, void *v)
{
	via_odev_to_seq(m, viaparinfo->shared->iga2_devices);
	return 0;
}