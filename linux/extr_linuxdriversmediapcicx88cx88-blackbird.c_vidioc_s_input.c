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
struct file {int dummy; } ;
struct cx88_core {int dummy; } ;
struct cx8802_dev {struct cx88_core* core; } ;
struct TYPE_2__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_1__ INPUT (unsigned int) ; 
 int /*<<< orphan*/  cx88_newstation (struct cx88_core*) ; 
 int /*<<< orphan*/  cx88_video_mux (struct cx88_core*,unsigned int) ; 
 struct cx8802_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_s_input(struct file *file, void *priv, unsigned int i)
{
	struct cx8802_dev *dev = video_drvdata(file);
	struct cx88_core *core = dev->core;

	if (i >= 4)
		return -EINVAL;
	if (!INPUT(i).type)
		return -EINVAL;

	cx88_newstation(core);
	cx88_video_mux(core, i);
	return 0;
}