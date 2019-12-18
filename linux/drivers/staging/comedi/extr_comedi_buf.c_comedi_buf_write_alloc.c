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
struct comedi_async {unsigned int buf_write_alloc_count; } ;

/* Variables and functions */
 unsigned int comedi_buf_write_n_unalloc (struct comedi_subdevice*) ; 
 int /*<<< orphan*/  smp_mb () ; 

unsigned int comedi_buf_write_alloc(struct comedi_subdevice *s,
				    unsigned int nbytes)
{
	struct comedi_async *async = s->async;
	unsigned int unalloc = comedi_buf_write_n_unalloc(s);

	if (nbytes > unalloc)
		nbytes = unalloc;

	async->buf_write_alloc_count += nbytes;

	/*
	 * ensure the async buffer 'counts' are read and updated
	 * before we write data to the write-alloc'ed buffer space
	 */
	smp_mb();

	return nbytes;
}