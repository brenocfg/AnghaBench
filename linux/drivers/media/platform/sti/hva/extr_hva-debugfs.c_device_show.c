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
struct seq_file {struct hva_dev* private; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct hva_dev {TYPE_2__* vdev; TYPE_1__ v4l2_dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  num; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int device_show(struct seq_file *s, void *data)
{
	struct hva_dev *hva = s->private;

	seq_printf(s, "[%s]\n", hva->v4l2_dev.name);
	seq_printf(s, "registered as /dev/video%d\n", hva->vdev->num);

	return 0;
}