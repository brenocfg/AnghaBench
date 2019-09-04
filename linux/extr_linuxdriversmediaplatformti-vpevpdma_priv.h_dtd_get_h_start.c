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
struct vpdma_dtd {int start_h_v; } ;

/* Variables and functions */
 int DTD_H_START_SHFT ; 

__attribute__((used)) static inline int dtd_get_h_start(struct vpdma_dtd *dtd)
{
	return dtd->start_h_v >> DTD_H_START_SHFT;
}