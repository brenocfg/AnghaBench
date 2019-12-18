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
struct l2t_entry {int state; int /*<<< orphan*/  arpq; } ;

/* Variables and functions */
#define  L2T_STATE_RESOLVING 132 
#define  L2T_STATE_STALE 131 
#define  L2T_STATE_SWITCHING 130 
#define  L2T_STATE_SYNC_WRITE 129 
#define  L2T_STATE_VALID 128 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static char l2e_state(const struct l2t_entry *e)
{
	switch (e->state) {
	case L2T_STATE_VALID: return 'V';
	case L2T_STATE_STALE: return 'S';
	case L2T_STATE_SYNC_WRITE: return 'W';
	case L2T_STATE_RESOLVING:
		return skb_queue_empty(&e->arpq) ? 'R' : 'A';
	case L2T_STATE_SWITCHING: return 'X';
	default:
		return 'U';
	}
}