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
struct vdec_common_if {int dummy; } ;

/* Variables and functions */
 struct vdec_common_if vdec_vp9_if ; 

struct vdec_common_if *get_vp9_dec_comm_if(void)
{
	return &vdec_vp9_if;
}