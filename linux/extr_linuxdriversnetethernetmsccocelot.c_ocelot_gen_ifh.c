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
struct frame_info {int port; int tag_type; int vid; } ;

/* Variables and functions */
 int IFH_INJ_BYPASS ; 

__attribute__((used)) static int ocelot_gen_ifh(u32 *ifh, struct frame_info *info)
{
	ifh[0] = IFH_INJ_BYPASS;
	ifh[1] = (0xf00 & info->port) >> 8;
	ifh[2] = (0xff & info->port) << 24;
	ifh[3] = (info->tag_type << 16) | info->vid;

	return 0;
}