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
struct ivtv_stream {int dummy; } ;
struct ivtv {int output_mode; struct ivtv_stream* streams; } ;

/* Variables and functions */
 size_t IVTV_DEC_STREAM_TYPE_MPG ; 
 size_t IVTV_DEC_STREAM_TYPE_YUV ; 
#define  OUT_MPG 129 
#define  OUT_YUV 128 

struct ivtv_stream *ivtv_get_output_stream(struct ivtv *itv)
{
	switch (itv->output_mode) {
	case OUT_MPG:
		return &itv->streams[IVTV_DEC_STREAM_TYPE_MPG];
	case OUT_YUV:
		return &itv->streams[IVTV_DEC_STREAM_TYPE_YUV];
	default:
		return NULL;
	}
}