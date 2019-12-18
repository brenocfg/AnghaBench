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
struct file {int dummy; } ;
struct cobalt_stream {unsigned int input; int /*<<< orphan*/  sd; int /*<<< orphan*/  q; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADV76XX_PAD_HDMI_PORT_A ; 
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  cobalt_enable_input (struct cobalt_stream*) ; 
 int /*<<< orphan*/  s_routing ; 
 int v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vb2_is_busy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video ; 
 struct cobalt_stream* video_drvdata (struct file*) ; 

__attribute__((used)) static int cobalt_s_input(struct file *file, void *priv_fh, unsigned int i)
{
	struct cobalt_stream *s = video_drvdata(file);

	if (i >= 2)
		return -EINVAL;
	if (vb2_is_busy(&s->q))
		return -EBUSY;
	s->input = i;

	cobalt_enable_input(s);

	if (s->input == 1) /* Test Pattern Generator */
		return 0;

	return v4l2_subdev_call(s->sd, video, s_routing,
			ADV76XX_PAD_HDMI_PORT_A, 0, 0);
}