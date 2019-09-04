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
typedef  size_t u16 ;
struct dtv_frontend_properties {int transmission_mode; int bandwidth_hz; } ;
struct dib8000_state {TYPE_1__** fe; } ;
struct TYPE_2__ {struct dtv_frontend_properties dtv_property_cache; } ;

/* Variables and functions */
 int* LUT_isdbt_symbol_duration ; 
#define  TRANSMISSION_MODE_2K 131 
#define  TRANSMISSION_MODE_4K 130 
#define  TRANSMISSION_MODE_8K 129 
#define  TRANSMISSION_MODE_AUTO 128 

__attribute__((used)) static u32 dib8000_get_symbol_duration(struct dib8000_state *state)
{
	struct dtv_frontend_properties *c = &state->fe[0]->dtv_property_cache;
	u16 i;

	switch (c->transmission_mode) {
	case TRANSMISSION_MODE_2K:
			i = 0;
			break;
	case TRANSMISSION_MODE_4K:
			i = 2;
			break;
	default:
	case TRANSMISSION_MODE_AUTO:
	case TRANSMISSION_MODE_8K:
			i = 1;
			break;
	}

	return (LUT_isdbt_symbol_duration[i] / (c->bandwidth_hz / 1000)) + 1;
}