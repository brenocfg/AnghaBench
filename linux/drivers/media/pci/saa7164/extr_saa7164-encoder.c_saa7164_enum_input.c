#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct v4l2_input {int index; int /*<<< orphan*/  std; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
struct file {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_INPUT_TYPE_CAMERA ; 
 int /*<<< orphan*/  V4L2_INPUT_TYPE_TUNER ; 
 TYPE_1__* saa7164_tvnorms ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char const* const,int) ; 

int saa7164_enum_input(struct file *file, void *priv, struct v4l2_input *i)
{
	static const char * const inputs[] = {
		"tuner", "composite", "svideo", "aux",
		"composite 2", "svideo 2", "aux 2"
	};
	int n;

	if (i->index >= 7)
		return -EINVAL;

	strscpy(i->name, inputs[i->index], sizeof(i->name));

	if (i->index == 0)
		i->type = V4L2_INPUT_TYPE_TUNER;
	else
		i->type  = V4L2_INPUT_TYPE_CAMERA;

	for (n = 0; n < ARRAY_SIZE(saa7164_tvnorms); n++)
		i->std |= saa7164_tvnorms[n].id;

	return 0;
}