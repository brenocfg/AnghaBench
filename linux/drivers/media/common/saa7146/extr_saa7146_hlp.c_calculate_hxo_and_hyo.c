#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct saa7146_vv {TYPE_1__* standard; } ;
struct TYPE_2__ {int v_offset; int h_offset; } ;

/* Variables and functions */
 int MASK_B0 ; 
 int MASK_B2 ; 
 int MASK_W0 ; 

__attribute__((used)) static void calculate_hxo_and_hyo(struct saa7146_vv *vv, u32* hps_h_scale, u32* hps_ctrl)
{
	int hyo = 0, hxo = 0;

	hyo = vv->standard->v_offset;
	hxo = vv->standard->h_offset;

	*hps_h_scale	&= ~(MASK_B0 | 0xf00);
	*hps_h_scale	|= (hxo <<  0);

	*hps_ctrl	&= ~(MASK_W0 | MASK_B2);
	*hps_ctrl	|= (hyo << 12);
}