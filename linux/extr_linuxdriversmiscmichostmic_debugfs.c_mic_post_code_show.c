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
struct seq_file {struct mic_device* private; } ;
struct mic_device {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* get_postcode ) (struct mic_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,int) ; 
 int stub1 (struct mic_device*) ; 

__attribute__((used)) static int mic_post_code_show(struct seq_file *s, void *pos)
{
	struct mic_device *mdev = s->private;
	u32 reg = mdev->ops->get_postcode(mdev);

	seq_printf(s, "%c%c", reg & 0xff, (reg >> 8) & 0xff);
	return 0;
}