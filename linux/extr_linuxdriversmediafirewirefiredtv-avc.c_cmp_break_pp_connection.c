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
typedef  scalar_t__ u64 ;
struct firedtv {int /*<<< orphan*/  device; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 scalar_t__ CMP_OUTPUT_PLUG_CONTROL_REG_0 ; 
 scalar_t__ cmp_lock (struct firedtv*,scalar_t__,scalar_t__*) ; 
 scalar_t__ cmp_read (struct firedtv*,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int get_opcr_channel (scalar_t__) ; 
 int /*<<< orphan*/  get_opcr_online (scalar_t__) ; 
 scalar_t__ get_opcr_p2p_connections (scalar_t__) ; 
 int /*<<< orphan*/  set_opcr_p2p_connections (scalar_t__*,scalar_t__) ; 

void cmp_break_pp_connection(struct firedtv *fdtv, int plug, int channel)
{
	__be32 old_opcr, opcr[2];
	u64 opcr_address = CMP_OUTPUT_PLUG_CONTROL_REG_0 + (plug << 2);
	int attempts = 0;

	if (cmp_read(fdtv, opcr_address, opcr) < 0)
		return;

repeat:
	if (!get_opcr_online(*opcr) || !get_opcr_p2p_connections(*opcr) ||
	    get_opcr_channel(*opcr) != channel) {
		dev_err(fdtv->device, "CMP: no connection to break\n");
		return;
	}

	old_opcr = *opcr;
	set_opcr_p2p_connections(opcr, get_opcr_p2p_connections(*opcr) - 1);

	opcr[1] = *opcr;
	opcr[0] = old_opcr;

	if (cmp_lock(fdtv, opcr_address, opcr) < 0)
		return;

	if (old_opcr != *opcr) {
		/*
		 * FIXME: if old_opcr.P2P_Connections == 1, i.e. we were last
		 * owner, deallocate isochronous channel and bandwidth at IRM
		 * if (...)
		 *	fdtv->backend->dealloc_resources(fdtv, channel, bw);
		 */

		if (++attempts < 6) /* arbitrary limit */
			goto repeat;
	}
}