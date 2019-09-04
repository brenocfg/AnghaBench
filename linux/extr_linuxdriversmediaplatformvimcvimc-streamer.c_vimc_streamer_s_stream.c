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
struct vimc_stream {int /*<<< orphan*/ * kthread; } ;
struct vimc_ent_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kthread_run (int /*<<< orphan*/ ,struct vimc_stream*,char*) ; 
 int kthread_stop (int /*<<< orphan*/ *) ; 
 int vimc_streamer_pipeline_init (struct vimc_stream*,struct vimc_ent_device*) ; 
 int /*<<< orphan*/  vimc_streamer_pipeline_terminate (struct vimc_stream*) ; 
 int /*<<< orphan*/  vimc_streamer_thread ; 

int vimc_streamer_s_stream(struct vimc_stream *stream,
			   struct vimc_ent_device *ved,
			   int enable)
{
	int ret;

	if (!stream || !ved)
		return -EINVAL;

	if (enable) {
		if (stream->kthread)
			return 0;

		ret = vimc_streamer_pipeline_init(stream, ved);
		if (ret)
			return ret;

		stream->kthread = kthread_run(vimc_streamer_thread, stream,
					      "vimc-streamer thread");

		if (IS_ERR(stream->kthread))
			return PTR_ERR(stream->kthread);

	} else {
		if (!stream->kthread)
			return 0;

		ret = kthread_stop(stream->kthread);
		if (ret)
			return ret;

		stream->kthread = NULL;

		vimc_streamer_pipeline_terminate(stream);
	}

	return 0;
}