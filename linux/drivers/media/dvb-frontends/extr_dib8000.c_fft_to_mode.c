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
#define  TRANSMISSION_MODE_2K 131 
#define  TRANSMISSION_MODE_4K 130 
#define  TRANSMISSION_MODE_8K 129 
#define  TRANSMISSION_MODE_AUTO 128 

__attribute__((used)) static u16 fft_to_mode(struct dib8000_state *state)
{
	u16 mode;
	switch (state->fe[0]->dtv_property_cache.transmission_mode) {
	case TRANSMISSION_MODE_2K:
		mode = 1;
		break;
	case TRANSMISSION_MODE_4K:
		mode = 2;
		break;
	default:
	case TRANSMISSION_MODE_AUTO:
	case TRANSMISSION_MODE_8K:
		mode = 3;
		break;
	}
	return mode;
}