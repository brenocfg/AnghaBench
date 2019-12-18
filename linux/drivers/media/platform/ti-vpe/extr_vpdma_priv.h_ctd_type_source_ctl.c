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
typedef  int u32 ;

/* Variables and functions */
 int CTD_PKT_TYPE ; 
 int CTD_PKT_TYPE_SHFT ; 
 int CTD_SOURCE_SHFT ; 

__attribute__((used)) static inline u32 ctd_type_source_ctl(int source, int control)
{
	return (CTD_PKT_TYPE << CTD_PKT_TYPE_SHFT) |
		(source << CTD_SOURCE_SHFT) | control;
}