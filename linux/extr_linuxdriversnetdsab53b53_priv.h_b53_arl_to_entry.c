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
typedef  int u64 ;
typedef  int u32 ;
struct b53_arl_entry {int port; int is_valid; int is_age; int is_static; int vid; int /*<<< orphan*/  mac; } ;

/* Variables and functions */
 int ARLTBL_AGE ; 
 int ARLTBL_DATA_PORT_ID_MASK ; 
 int ARLTBL_STATIC ; 
 int ARLTBL_VALID ; 
 int ARLTBL_VID_S ; 
 int /*<<< orphan*/  memset (struct b53_arl_entry*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  u64_to_ether_addr (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void b53_arl_to_entry(struct b53_arl_entry *ent,
				    u64 mac_vid, u32 fwd_entry)
{
	memset(ent, 0, sizeof(*ent));
	ent->port = fwd_entry & ARLTBL_DATA_PORT_ID_MASK;
	ent->is_valid = !!(fwd_entry & ARLTBL_VALID);
	ent->is_age = !!(fwd_entry & ARLTBL_AGE);
	ent->is_static = !!(fwd_entry & ARLTBL_STATIC);
	u64_to_ether_addr(mac_vid, ent->mac);
	ent->vid = mac_vid >> ARLTBL_VID_S;
}