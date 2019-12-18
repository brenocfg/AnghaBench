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
typedef  int /*<<< orphan*/  u32 ;
struct ivtv_buffer {int bytesused; scalar_t__ buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  swab32s (int /*<<< orphan*/ *) ; 

void ivtv_buf_swap(struct ivtv_buffer *buf)
{
	int i;

	for (i = 0; i < buf->bytesused; i += 4)
		swab32s((u32 *)(buf->buf + i));
}