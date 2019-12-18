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
struct cudbg_compress_hdr {int dummy; } ;
struct cudbg_buffer {scalar_t__ offset; scalar_t__ size; char* data; } ;

/* Variables and functions */
 int CUDBG_STATUS_NO_MEM ; 

__attribute__((used)) static int cudbg_get_compress_hdr(struct cudbg_buffer *pdbg_buff,
				  struct cudbg_buffer *pin_buff)
{
	if (pdbg_buff->offset + sizeof(struct cudbg_compress_hdr) >
	    pdbg_buff->size)
		return CUDBG_STATUS_NO_MEM;

	pin_buff->data = (char *)pdbg_buff->data + pdbg_buff->offset;
	pin_buff->offset = 0;
	pin_buff->size = sizeof(struct cudbg_compress_hdr);
	pdbg_buff->offset += sizeof(struct cudbg_compress_hdr);
	return 0;
}