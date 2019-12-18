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
typedef  size_t u16 ;
struct brcmf_flowring_ring {int /*<<< orphan*/  status; } ;
struct brcmf_flowring {struct brcmf_flowring_ring** rings; } ;

/* Variables and functions */
 int /*<<< orphan*/  RING_OPEN ; 
 int /*<<< orphan*/  brcmf_err (char*,size_t) ; 

void brcmf_flowring_open(struct brcmf_flowring *flow, u16 flowid)
{
	struct brcmf_flowring_ring *ring;

	ring = flow->rings[flowid];
	if (!ring) {
		brcmf_err("Ring NULL, for flowid %d\n", flowid);
		return;
	}

	ring->status = RING_OPEN;
}