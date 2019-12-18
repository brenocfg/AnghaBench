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
struct vpdma_ctd {int fid_ctl; } ;

/* Variables and functions */
 int CTD_FID2_MASK ; 

__attribute__((used)) static inline int ctd_get_fid0_ctl(struct vpdma_ctd *ctd)
{
	return ctd->fid_ctl & CTD_FID2_MASK;
}