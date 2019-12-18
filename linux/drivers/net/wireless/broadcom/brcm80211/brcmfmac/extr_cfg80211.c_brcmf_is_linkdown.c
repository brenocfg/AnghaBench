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
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct brcmf_event_msg {scalar_t__ event_code; int flags; } ;

/* Variables and functions */
 int BRCMF_EVENT_MSG_LINK ; 
 scalar_t__ BRCMF_E_DEAUTH ; 
 scalar_t__ BRCMF_E_DEAUTH_IND ; 
 scalar_t__ BRCMF_E_DISASSOC_IND ; 
 scalar_t__ BRCMF_E_LINK ; 
 int /*<<< orphan*/  CONN ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool brcmf_is_linkdown(const struct brcmf_event_msg *e)
{
	u32 event = e->event_code;
	u16 flags = e->flags;

	if ((event == BRCMF_E_DEAUTH) || (event == BRCMF_E_DEAUTH_IND) ||
	    (event == BRCMF_E_DISASSOC_IND) ||
	    ((event == BRCMF_E_LINK) && (!(flags & BRCMF_EVENT_MSG_LINK)))) {
		brcmf_dbg(CONN, "Processing link down\n");
		return true;
	}
	return false;
}