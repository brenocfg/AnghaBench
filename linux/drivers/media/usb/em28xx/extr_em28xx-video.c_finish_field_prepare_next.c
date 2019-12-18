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
struct em28xx_v4l2 {scalar_t__ top_field; scalar_t__ progressive; } ;
struct em28xx_dmaqueue {int dummy; } ;
struct em28xx_buffer {scalar_t__ pos; scalar_t__ top_field; } ;
struct em28xx {struct em28xx_v4l2* v4l2; } ;

/* Variables and functions */
 int /*<<< orphan*/  finish_buffer (struct em28xx*,struct em28xx_buffer*) ; 
 struct em28xx_buffer* get_next_buf (struct em28xx*,struct em28xx_dmaqueue*) ; 

__attribute__((used)) static struct em28xx_buffer *
finish_field_prepare_next(struct em28xx *dev,
			  struct em28xx_buffer *buf,
			  struct em28xx_dmaqueue *dma_q)
{
	struct em28xx_v4l2 *v4l2 = dev->v4l2;

	if (v4l2->progressive || v4l2->top_field) { /* Brand new frame */
		if (buf)
			finish_buffer(dev, buf);
		buf = get_next_buf(dev, dma_q);
	}
	if (buf) {
		buf->top_field = v4l2->top_field;
		buf->pos = 0;
	}

	return buf;
}