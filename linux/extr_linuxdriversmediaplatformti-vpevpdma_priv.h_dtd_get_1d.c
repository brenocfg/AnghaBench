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
struct vpdma_dtd {int type_ctl_stride; } ;

/* Variables and functions */
 int DTD_1D_MASK ; 
 int DTD_1D_SHFT ; 

__attribute__((used)) static inline bool dtd_get_1d(struct vpdma_dtd *dtd)
{
	return (dtd->type_ctl_stride >> DTD_1D_SHFT) & DTD_1D_MASK;
}