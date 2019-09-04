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
struct vpdma_ctd {int type_source_ctl; } ;

/* Variables and functions */
 int CTD_PKT_TYPE_SHFT ; 

__attribute__((used)) static inline int ctd_get_pkt_type(struct vpdma_ctd *ctd)
{
	return ctd->type_source_ctl >> CTD_PKT_TYPE_SHFT;
}