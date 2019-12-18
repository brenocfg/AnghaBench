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
struct dm_buffer {int dummy; } ;
struct buffer_aux {scalar_t__ hash_verified; } ;

/* Variables and functions */
 struct buffer_aux* dm_bufio_get_aux_data (struct dm_buffer*) ; 

__attribute__((used)) static void dm_bufio_alloc_callback(struct dm_buffer *buf)
{
	struct buffer_aux *aux = dm_bufio_get_aux_data(buf);

	aux->hash_verified = 0;
}