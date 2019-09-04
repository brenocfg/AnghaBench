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
struct dtv_frontend_properties {int transmission_mode; int guard_interval; } ;
struct TYPE_3__ {int diversity_delay; } ;
struct dib8000_state {TYPE_1__ cfg; TYPE_2__** fe; } ;
struct TYPE_4__ {struct dtv_frontend_properties dtv_property_cache; } ;

/* Variables and functions */
#define  TRANSMISSION_MODE_2K 130 
#define  TRANSMISSION_MODE_4K 129 
#define  TRANSMISSION_MODE_8K 128 
 int dib8000_read_word (struct dib8000_state*,int) ; 
 int /*<<< orphan*/  dib8000_write_word (struct dib8000_state*,int,int) ; 

__attribute__((used)) static void dib8000_set_sync_wait(struct dib8000_state *state)
{
	struct dtv_frontend_properties *c = &state->fe[0]->dtv_property_cache;
	u16 sync_wait = 64;

	/* P_dvsy_sync_wait - reuse mode */
	switch (c->transmission_mode) {
	case TRANSMISSION_MODE_8K:
			sync_wait = 256;
			break;
	case TRANSMISSION_MODE_4K:
			sync_wait = 128;
			break;
	default:
	case TRANSMISSION_MODE_2K:
			sync_wait =  64;
			break;
	}

	if (state->cfg.diversity_delay == 0)
		sync_wait = (sync_wait * (1 << (c->guard_interval)) * 3) / 2 + 48; /* add 50% SFN margin + compensate for one DVSY-fifo */
	else
		sync_wait = (sync_wait * (1 << (c->guard_interval)) * 3) / 2 + state->cfg.diversity_delay; /* add 50% SFN margin + compensate for DVSY-fifo */

	dib8000_write_word(state, 273, (dib8000_read_word(state, 273) & 0x000f) | (sync_wait << 4));
}