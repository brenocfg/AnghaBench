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
struct go7007 {unsigned int input; int /*<<< orphan*/  vidq; TYPE_1__* board_info; } ;
struct file {int dummy; } ;
struct TYPE_2__ {unsigned int num_inputs; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  go7007_s_input (struct go7007*) ; 
 scalar_t__ vb2_is_busy (int /*<<< orphan*/ *) ; 
 struct go7007* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_s_input(struct file *file, void *priv, unsigned int input)
{
	struct go7007 *go = video_drvdata(file);

	if (input >= go->board_info->num_inputs)
		return -EINVAL;
	if (vb2_is_busy(&go->vidq))
		return -EBUSY;

	go->input = input;
	go7007_s_input(go);

	return 0;
}