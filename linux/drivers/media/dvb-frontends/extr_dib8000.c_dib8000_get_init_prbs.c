#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct dib8000_state {TYPE_2__** fe; } ;
struct TYPE_3__ {int transmission_mode; } ;
struct TYPE_4__ {TYPE_1__ dtv_property_cache; } ;

/* Variables and functions */
#define  TRANSMISSION_MODE_2K 130 
#define  TRANSMISSION_MODE_4K 129 
#define  TRANSMISSION_MODE_8K 128 
 int /*<<< orphan*/  dprintk (char*,int,int,int) ; 
 int* lut_prbs_2k ; 
 int* lut_prbs_4k ; 
 int* lut_prbs_8k ; 

__attribute__((used)) static u16 dib8000_get_init_prbs(struct dib8000_state *state, u16 subchannel)
{
	int sub_channel_prbs_group = 0;

	sub_channel_prbs_group = (subchannel / 3) + 1;
	dprintk("sub_channel_prbs_group = %d , subchannel =%d prbs = 0x%04x\n", sub_channel_prbs_group, subchannel, lut_prbs_8k[sub_channel_prbs_group]);

	switch (state->fe[0]->dtv_property_cache.transmission_mode) {
	case TRANSMISSION_MODE_2K:
			return lut_prbs_2k[sub_channel_prbs_group];
	case TRANSMISSION_MODE_4K:
			return lut_prbs_4k[sub_channel_prbs_group];
	default:
	case TRANSMISSION_MODE_8K:
			return lut_prbs_8k[sub_channel_prbs_group];
	}
}