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
 int /*<<< orphan*/  FIFODATA ; 
 int /*<<< orphan*/  nsp_multi_read_2 (unsigned int,int /*<<< orphan*/ ,void*,unsigned long) ; 

__attribute__((used)) static inline void nsp_fifo16_read(unsigned int   base,
				   void          *buf,
				   unsigned long  count)
{
	//nsp_dbg(NSP_DEBUG_DATA_IO, "buf=0x%p, count=0x%lx*2", buf, count);
	nsp_multi_read_2(base, FIFODATA, buf, count);
}