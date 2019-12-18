#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vsp1_pipeline {int partitions; TYPE_1__* output; } ;
struct vsp1_partition_window {unsigned int left; unsigned int width; } ;
struct vsp1_partition {int dummy; } ;
struct v4l2_mbus_framefmt {unsigned int width; } ;
struct TYPE_4__ {int /*<<< orphan*/  config; } ;
struct TYPE_3__ {TYPE_2__ entity; } ;

/* Variables and functions */
 int /*<<< orphan*/  RWPF_PAD_SINK ; 
 struct v4l2_mbus_framefmt* vsp1_entity_get_pad_format (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vsp1_pipeline_propagate_partition (struct vsp1_pipeline*,struct vsp1_partition*,unsigned int,struct vsp1_partition_window*) ; 

__attribute__((used)) static void vsp1_video_calculate_partition(struct vsp1_pipeline *pipe,
					   struct vsp1_partition *partition,
					   unsigned int div_size,
					   unsigned int index)
{
	const struct v4l2_mbus_framefmt *format;
	struct vsp1_partition_window window;
	unsigned int modulus;

	/*
	 * Partitions are computed on the size before rotation, use the format
	 * at the WPF sink.
	 */
	format = vsp1_entity_get_pad_format(&pipe->output->entity,
					    pipe->output->entity.config,
					    RWPF_PAD_SINK);

	/* A single partition simply processes the output size in full. */
	if (pipe->partitions <= 1) {
		window.left = 0;
		window.width = format->width;

		vsp1_pipeline_propagate_partition(pipe, partition, index,
						  &window);
		return;
	}

	/* Initialise the partition with sane starting conditions. */
	window.left = index * div_size;
	window.width = div_size;

	modulus = format->width % div_size;

	/*
	 * We need to prevent the last partition from being smaller than the
	 * *minimum* width of the hardware capabilities.
	 *
	 * If the modulus is less than half of the partition size,
	 * the penultimate partition is reduced to half, which is added
	 * to the final partition: |1234|1234|1234|12|341|
	 * to prevent this:        |1234|1234|1234|1234|1|.
	 */
	if (modulus) {
		/*
		 * pipe->partitions is 1 based, whilst index is a 0 based index.
		 * Normalise this locally.
		 */
		unsigned int partitions = pipe->partitions - 1;

		if (modulus < div_size / 2) {
			if (index == partitions - 1) {
				/* Halve the penultimate partition. */
				window.width = div_size / 2;
			} else if (index == partitions) {
				/* Increase the final partition. */
				window.width = (div_size / 2) + modulus;
				window.left -= div_size / 2;
			}
		} else if (index == partitions) {
			window.width = modulus;
		}
	}

	vsp1_pipeline_propagate_partition(pipe, partition, index, &window);
}