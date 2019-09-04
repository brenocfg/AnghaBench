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

/* Variables and functions */
 int /*<<< orphan*/  BYTE_COPY_FWD (unsigned long,unsigned long,unsigned int) ; 

void *memcpyb(void *dstpp, const void *srcpp, unsigned len)
{
	unsigned long int dstp = (long int) dstpp;
	unsigned long int srcp = (long int) srcpp;

	BYTE_COPY_FWD(dstp, srcp, len);

	return dstpp;
}