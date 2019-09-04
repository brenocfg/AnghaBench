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
 int DTD_FIELD_MASK ; 
 int DTD_FIELD_SHFT ; 

__attribute__((used)) static inline int dtd_get_field(struct vpdma_dtd *dtd)
{
	return (dtd->type_ctl_stride >> DTD_FIELD_SHFT) & DTD_FIELD_MASK;
}