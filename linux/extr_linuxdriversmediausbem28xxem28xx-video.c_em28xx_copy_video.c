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
struct em28xx_v4l2 {int width; scalar_t__ progressive; } ;
struct em28xx_buffer {unsigned long pos; unsigned long length; void* vb_buf; scalar_t__ top_field; } ;
struct em28xx {struct em28xx_v4l2* v4l2; } ;

/* Variables and functions */
 int /*<<< orphan*/  em28xx_isocdbg (char*,int) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 

__attribute__((used)) static void em28xx_copy_video(struct em28xx *dev,
			      struct em28xx_buffer *buf,
			      unsigned char *usb_buf,
			      unsigned long len)
{
	struct em28xx_v4l2 *v4l2 = dev->v4l2;
	void *fieldstart, *startwrite, *startread;
	int  linesdone, currlinedone, offset, lencopy, remain;
	int bytesperline = v4l2->width << 1;

	if (buf->pos + len > buf->length)
		len = buf->length - buf->pos;

	startread = usb_buf;
	remain = len;

	if (v4l2->progressive || buf->top_field)
		fieldstart = buf->vb_buf;
	else /* interlaced mode, even nr. of lines */
		fieldstart = buf->vb_buf + bytesperline;

	linesdone = buf->pos / bytesperline;
	currlinedone = buf->pos % bytesperline;

	if (v4l2->progressive)
		offset = linesdone * bytesperline + currlinedone;
	else
		offset = linesdone * bytesperline * 2 + currlinedone;

	startwrite = fieldstart + offset;
	lencopy = bytesperline - currlinedone;
	lencopy = lencopy > remain ? remain : lencopy;

	if ((char *)startwrite + lencopy > (char *)buf->vb_buf + buf->length) {
		em28xx_isocdbg("Overflow of %zu bytes past buffer end (1)\n",
			       ((char *)startwrite + lencopy) -
			      ((char *)buf->vb_buf + buf->length));
		remain = (char *)buf->vb_buf + buf->length -
			 (char *)startwrite;
		lencopy = remain;
	}
	if (lencopy <= 0)
		return;
	memcpy(startwrite, startread, lencopy);

	remain -= lencopy;

	while (remain > 0) {
		if (v4l2->progressive)
			startwrite += lencopy;
		else
			startwrite += lencopy + bytesperline;
		startread += lencopy;
		if (bytesperline > remain)
			lencopy = remain;
		else
			lencopy = bytesperline;

		if ((char *)startwrite + lencopy > (char *)buf->vb_buf +
		    buf->length) {
			em28xx_isocdbg("Overflow of %zu bytes past buffer end(2)\n",
				       ((char *)startwrite + lencopy) -
				       ((char *)buf->vb_buf + buf->length));
			remain = (char *)buf->vb_buf + buf->length -
				 (char *)startwrite;
			lencopy = remain;
		}
		if (lencopy <= 0)
			break;

		memcpy(startwrite, startread, lencopy);

		remain -= lencopy;
	}

	buf->pos += len;
}