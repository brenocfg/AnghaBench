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
typedef  void* u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct libipw_snap_hdr {int dsap; int ssap; int ctrl; void** oui; } ;
typedef  scalar_t__ __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_AARP ; 
 int /*<<< orphan*/  ETH_P_IPX ; 
 void** P802_1H_OUI ; 
 void** RFC1042_OUI ; 
 int SNAP_SIZE ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void**,scalar_t__*,int) ; 

__attribute__((used)) static int libipw_copy_snap(u8 * data, __be16 h_proto)
{
	struct libipw_snap_hdr *snap;
	u8 *oui;

	snap = (struct libipw_snap_hdr *)data;
	snap->dsap = 0xaa;
	snap->ssap = 0xaa;
	snap->ctrl = 0x03;

	if (h_proto == htons(ETH_P_AARP) || h_proto == htons(ETH_P_IPX))
		oui = P802_1H_OUI;
	else
		oui = RFC1042_OUI;
	snap->oui[0] = oui[0];
	snap->oui[1] = oui[1];
	snap->oui[2] = oui[2];

	memcpy(data + SNAP_SIZE, &h_proto, sizeof(u16));

	return SNAP_SIZE + sizeof(u16);
}