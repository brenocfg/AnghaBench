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
struct comedi_subdevice {struct comedi_async* async; } ;
struct comedi_async {unsigned int buf_read_ptr; unsigned int prealloc_bufsz; void* prealloc_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,void*,unsigned int) ; 

__attribute__((used)) static void comedi_buf_memcpy_from(struct comedi_subdevice *s,
				   void *dest, unsigned int nbytes)
{
	void *src;
	struct comedi_async *async = s->async;
	unsigned int read_ptr = async->buf_read_ptr;

	while (nbytes) {
		unsigned int block_size;

		src = async->prealloc_buf + read_ptr;

		if (nbytes >= async->prealloc_bufsz - read_ptr)
			block_size = async->prealloc_bufsz - read_ptr;
		else
			block_size = nbytes;

		memcpy(dest, src, block_size);
		nbytes -= block_size;
		dest += block_size;
		read_ptr = 0;
	}
}