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
struct v4l2_streamparm {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  source; } ;
struct stm32_dcmi {TYPE_1__ entity; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int v4l2_g_parm_cap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_streamparm*) ; 
 int /*<<< orphan*/  video_devdata (struct file*) ; 
 struct stm32_dcmi* video_drvdata (struct file*) ; 

__attribute__((used)) static int dcmi_g_parm(struct file *file, void *priv,
		       struct v4l2_streamparm *p)
{
	struct stm32_dcmi *dcmi = video_drvdata(file);

	return v4l2_g_parm_cap(video_devdata(file), dcmi->entity.source, p);
}