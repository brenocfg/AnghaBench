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
struct vpdma_dtd {int max_width_height; } ;

/* Variables and functions */
 int DTD_MAX_HEIGHT_MASK ; 
 int DTD_MAX_HEIGHT_SHFT ; 

__attribute__((used)) static inline int dtd_get_max_height(struct vpdma_dtd *dtd)
{
	return (dtd->max_width_height >> DTD_MAX_HEIGHT_SHFT) &
							DTD_MAX_HEIGHT_MASK;
}