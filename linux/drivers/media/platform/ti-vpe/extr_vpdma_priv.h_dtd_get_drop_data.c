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
struct vpdma_dtd {int desc_write_addr; } ;

/* Variables and functions */
 int DTD_DROP_DATA_MASK ; 
 int DTD_DROP_DATA_SHIFT ; 

__attribute__((used)) static inline bool dtd_get_drop_data(struct vpdma_dtd *dtd)
{
	return (dtd->desc_write_addr >> DTD_DROP_DATA_SHIFT) &
							DTD_DROP_DATA_MASK;
}