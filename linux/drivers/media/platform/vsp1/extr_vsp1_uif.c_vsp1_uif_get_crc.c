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
typedef  int /*<<< orphan*/  u32 ;
struct vsp1_uif {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VI6_UIF_DISCOM_DOCMCCRCR ; 
 int /*<<< orphan*/  vsp1_uif_read (struct vsp1_uif*,int /*<<< orphan*/ ) ; 

u32 vsp1_uif_get_crc(struct vsp1_uif *uif)
{
	return vsp1_uif_read(uif, VI6_UIF_DISCOM_DOCMCCRCR);
}