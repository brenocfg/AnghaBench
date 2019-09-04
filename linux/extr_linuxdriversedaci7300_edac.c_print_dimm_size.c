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
struct i7300_pvt {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void print_dimm_size(struct i7300_pvt *pvt)
{
#ifdef CONFIG_EDAC_DEBUG
	struct i7300_dimm_info *dinfo;
	char *p;
	int space, n;
	int channel, slot;

	space = PAGE_SIZE;
	p = pvt->tmp_prt_buffer;

	n = snprintf(p, space, "              ");
	p += n;
	space -= n;
	for (channel = 0; channel < MAX_CHANNELS; channel++) {
		n = snprintf(p, space, "channel %d | ", channel);
		p += n;
		space -= n;
	}
	edac_dbg(2, "%s\n", pvt->tmp_prt_buffer);
	p = pvt->tmp_prt_buffer;
	space = PAGE_SIZE;
	n = snprintf(p, space, "-------------------------------"
			       "------------------------------");
	p += n;
	space -= n;
	edac_dbg(2, "%s\n", pvt->tmp_prt_buffer);
	p = pvt->tmp_prt_buffer;
	space = PAGE_SIZE;

	for (slot = 0; slot < MAX_SLOTS; slot++) {
		n = snprintf(p, space, "csrow/SLOT %d  ", slot);
		p += n;
		space -= n;

		for (channel = 0; channel < MAX_CHANNELS; channel++) {
			dinfo = &pvt->dimm_info[slot][channel];
			n = snprintf(p, space, "%4d MB   | ", dinfo->megabytes);
			p += n;
			space -= n;
		}

		edac_dbg(2, "%s\n", pvt->tmp_prt_buffer);
		p = pvt->tmp_prt_buffer;
		space = PAGE_SIZE;
	}

	n = snprintf(p, space, "-------------------------------"
			       "------------------------------");
	p += n;
	space -= n;
	edac_dbg(2, "%s\n", pvt->tmp_prt_buffer);
	p = pvt->tmp_prt_buffer;
	space = PAGE_SIZE;
#endif
}