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
struct ssp_msg {int /*<<< orphan*/ * buffer; } ;

/* Variables and functions */
 unsigned int SSP_HEADER_SIZE_ALIGNED ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static inline void ssp_get_buffer(struct ssp_msg *m, unsigned int offset,
				  void *dest, unsigned int len)
{
	memcpy(dest, &m->buffer[SSP_HEADER_SIZE_ALIGNED + offset],  len);
}