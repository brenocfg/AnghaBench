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
typedef  size_t u8 ;
typedef  size_t u32 ;

/* Variables and functions */
 size_t qed_cyclic_add (size_t,int,size_t) ; 

__attribute__((used)) static u32 qed_read_from_cyclic_buf(void *buf,
				    u32 *offset,
				    u32 buf_size, u8 num_bytes_to_read)
{
	u8 i, *val_ptr, *bytes_buf = (u8 *)buf;
	u32 val = 0;

	val_ptr = (u8 *)&val;

	/* Assume running on a LITTLE ENDIAN and the buffer is network order
	 * (BIG ENDIAN), as high order bytes are placed in lower memory address.
	 */
	for (i = 0; i < num_bytes_to_read; i++) {
		val_ptr[i] = bytes_buf[*offset];
		*offset = qed_cyclic_add(*offset, 1, buf_size);
	}

	return val;
}