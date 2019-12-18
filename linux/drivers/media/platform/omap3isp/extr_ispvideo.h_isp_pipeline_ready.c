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
struct isp_pipeline {int state; } ;

/* Variables and functions */
 int ISP_PIPELINE_IDLE_INPUT ; 
 int ISP_PIPELINE_IDLE_OUTPUT ; 
 int ISP_PIPELINE_QUEUE_INPUT ; 
 int ISP_PIPELINE_QUEUE_OUTPUT ; 
 int ISP_PIPELINE_STREAM_INPUT ; 
 int ISP_PIPELINE_STREAM_OUTPUT ; 

__attribute__((used)) static inline int isp_pipeline_ready(struct isp_pipeline *pipe)
{
	return pipe->state == (ISP_PIPELINE_STREAM_INPUT |
			       ISP_PIPELINE_STREAM_OUTPUT |
			       ISP_PIPELINE_QUEUE_INPUT |
			       ISP_PIPELINE_QUEUE_OUTPUT |
			       ISP_PIPELINE_IDLE_INPUT |
			       ISP_PIPELINE_IDLE_OUTPUT);
}