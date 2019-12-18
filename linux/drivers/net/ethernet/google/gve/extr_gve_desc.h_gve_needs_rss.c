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
typedef  int __be16 ;

/* Variables and functions */
 int GVE_RXF_FRAG ; 
 int GVE_RXF_IPV4 ; 
 int GVE_RXF_IPV6 ; 

__attribute__((used)) static inline bool gve_needs_rss(__be16 flag)
{
	if (flag & GVE_RXF_FRAG)
		return false;
	if (flag & (GVE_RXF_IPV4 | GVE_RXF_IPV6))
		return true;
	return false;
}