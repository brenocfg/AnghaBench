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
struct iio_buffer {size_t bytes_per_datum; } ;

/* Variables and functions */
 int /*<<< orphan*/  iio_mark_update_needed_kfifo (struct iio_buffer*) ; 

__attribute__((used)) static int iio_set_bytes_per_datum_kfifo(struct iio_buffer *r, size_t bpd)
{
	if (r->bytes_per_datum != bpd) {
		r->bytes_per_datum = bpd;
		iio_mark_update_needed_kfifo(r);
	}
	return 0;
}