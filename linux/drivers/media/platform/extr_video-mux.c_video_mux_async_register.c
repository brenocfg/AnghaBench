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
struct video_mux {int /*<<< orphan*/  subdev; } ;
struct v4l2_async_subdev {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int* kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (unsigned int*) ; 
 int v4l2_async_register_fwnode_subdev (int /*<<< orphan*/ *,int,unsigned int*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_mux_parse_endpoint ; 

__attribute__((used)) static int video_mux_async_register(struct video_mux *vmux,
				    unsigned int num_input_pads)
{
	unsigned int i, *ports;
	int ret;

	ports = kcalloc(num_input_pads, sizeof(*ports), GFP_KERNEL);
	if (!ports)
		return -ENOMEM;
	for (i = 0; i < num_input_pads; i++)
		ports[i] = i;

	ret = v4l2_async_register_fwnode_subdev(
		&vmux->subdev, sizeof(struct v4l2_async_subdev),
		ports, num_input_pads, video_mux_parse_endpoint);

	kfree(ports);
	return ret;
}