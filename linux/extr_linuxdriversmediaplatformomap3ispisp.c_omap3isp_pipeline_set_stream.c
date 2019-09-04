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
struct isp_pipeline {int stream_state; } ;
typedef  enum isp_pipeline_stream_state { ____Placeholder_isp_pipeline_stream_state } isp_pipeline_stream_state ;

/* Variables and functions */
 int ISP_PIPELINE_STREAM_STOPPED ; 
 int isp_pipeline_disable (struct isp_pipeline*) ; 
 int isp_pipeline_enable (struct isp_pipeline*,int) ; 

int omap3isp_pipeline_set_stream(struct isp_pipeline *pipe,
				 enum isp_pipeline_stream_state state)
{
	int ret;

	if (state == ISP_PIPELINE_STREAM_STOPPED)
		ret = isp_pipeline_disable(pipe);
	else
		ret = isp_pipeline_enable(pipe, state);

	if (ret == 0 || state == ISP_PIPELINE_STREAM_STOPPED)
		pipe->stream_state = state;

	return ret;
}