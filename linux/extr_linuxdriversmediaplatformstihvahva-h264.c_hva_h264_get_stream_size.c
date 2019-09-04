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
struct hva_h264_po {unsigned int bitstream_size; } ;
struct hva_h264_task {struct hva_h264_po po; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int hva_h264_get_stream_size(struct hva_h264_task *task)
{
	struct hva_h264_po *po = &task->po;

	return po->bitstream_size;
}