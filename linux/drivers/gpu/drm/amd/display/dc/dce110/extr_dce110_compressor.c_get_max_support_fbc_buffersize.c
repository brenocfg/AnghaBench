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
 unsigned int FBC_MAX_X ; 
 unsigned int FBC_MAX_Y ; 

void get_max_support_fbc_buffersize(unsigned int *max_x, unsigned int *max_y)
{
	*max_x = FBC_MAX_X;
	*max_y = FBC_MAX_Y;

	/* if (m_smallLocalFrameBufferMemory == 1)
	 * {
	 *	*max_x = FBC_MAX_X_SG;
	 *	*max_y = FBC_MAX_Y_SG;
	 * }
	 */
}