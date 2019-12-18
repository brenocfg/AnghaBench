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
struct tw68_dev {unsigned int input; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  TW68_INFORM ; 
 unsigned int TW68_INPUT_MAX ; 
 int /*<<< orphan*/  tw_andorb (int /*<<< orphan*/ ,int,int) ; 
 struct tw68_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int tw68_s_input(struct file *file, void *priv, unsigned int i)
{
	struct tw68_dev *dev = video_drvdata(file);

	if (i >= TW68_INPUT_MAX)
		return -EINVAL;
	dev->input = i;
	tw_andorb(TW68_INFORM, 0x03 << 2, dev->input << 2);
	return 0;
}