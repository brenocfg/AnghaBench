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
typedef  int /*<<< orphan*/  v4l2_std_id ;
struct tw68_dev {TYPE_1__* tvnorm; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 struct tw68_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int tw68_g_std(struct file *file, void *priv, v4l2_std_id *id)
{
	struct tw68_dev *dev = video_drvdata(file);

	*id = dev->tvnorm->id;
	return 0;
}