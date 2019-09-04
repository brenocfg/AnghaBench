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
struct vpdma_ctd {int pixel_line_count; } ;

/* Variables and functions */
 int CTD_LINE_COUNT_MASK ; 

__attribute__((used)) static inline int ctd_get_line_count(struct vpdma_ctd *ctd)
{
	return ctd->pixel_line_count & CTD_LINE_COUNT_MASK;
}