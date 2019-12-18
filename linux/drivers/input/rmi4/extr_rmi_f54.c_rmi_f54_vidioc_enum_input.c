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
struct v4l2_input {int /*<<< orphan*/  name; int /*<<< orphan*/  type; int /*<<< orphan*/  index; } ;
struct file {int dummy; } ;
struct f54_data {int dummy; } ;
typedef  enum rmi_f54_report_type { ____Placeholder_rmi_f54_report_type } rmi_f54_report_type ;

/* Variables and functions */
 int EINVAL ; 
 int F54_REPORT_NONE ; 
 int /*<<< orphan*/  V4L2_INPUT_TYPE_TOUCH ; 
 int rmi_f54_get_reptype (struct f54_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * rmi_f54_report_type_names ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct f54_data* video_drvdata (struct file*) ; 

__attribute__((used)) static int rmi_f54_vidioc_enum_input(struct file *file, void *priv,
				     struct v4l2_input *i)
{
	struct f54_data *f54 = video_drvdata(file);
	enum rmi_f54_report_type reptype;

	reptype = rmi_f54_get_reptype(f54, i->index);
	if (reptype == F54_REPORT_NONE)
		return -EINVAL;

	i->type = V4L2_INPUT_TYPE_TOUCH;

	strlcpy(i->name, rmi_f54_report_type_names[reptype], sizeof(i->name));
	return 0;
}