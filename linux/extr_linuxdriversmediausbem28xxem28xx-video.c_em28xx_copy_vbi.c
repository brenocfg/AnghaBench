#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct em28xx_buffer {unsigned long pos; unsigned long length; scalar_t__ top_field; scalar_t__ vb_buf; } ;
struct em28xx {TYPE_1__* v4l2; } ;
struct TYPE_2__ {unsigned int vbi_width; unsigned int vbi_height; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (scalar_t__,unsigned char*,unsigned long) ; 

__attribute__((used)) static void em28xx_copy_vbi(struct em28xx *dev,
			    struct em28xx_buffer *buf,
			    unsigned char *usb_buf,
			    unsigned long len)
{
	unsigned int offset;

	if (buf->pos + len > buf->length)
		len = buf->length - buf->pos;

	offset = buf->pos;
	/* Make sure the bottom field populates the second half of the frame */
	if (buf->top_field == 0)
		offset += dev->v4l2->vbi_width * dev->v4l2->vbi_height;

	memcpy(buf->vb_buf + offset, usb_buf, len);
	buf->pos += len;
}