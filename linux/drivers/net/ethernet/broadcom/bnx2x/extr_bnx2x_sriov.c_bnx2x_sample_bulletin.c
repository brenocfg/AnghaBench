#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  union pf_vf_bulletin {int dummy; } pf_vf_bulletin ;
typedef  scalar_t__ u32 ;
struct pf_vf_bulletin_content {scalar_t__ crc; scalar_t__ version; int valid_bitmap; int link_flags; int /*<<< orphan*/  link_speed; struct pf_vf_bulletin_content* mac; } ;
struct TYPE_6__ {scalar_t__ version; int /*<<< orphan*/  mac; struct pf_vf_bulletin_content content; } ;
struct TYPE_5__ {scalar_t__ link_report_flags; int /*<<< orphan*/  line_speed; } ;
struct bnx2x {TYPE_3__ old_bulletin; TYPE_2__ vf_link_vars; TYPE_1__* dev; TYPE_3__ shadow_bulletin; struct pf_vf_bulletin_content* pf2vf_bulletin; } ;
typedef  enum sample_bulletin_result { ____Placeholder_sample_bulletin_result } sample_bulletin_result ;
struct TYPE_4__ {TYPE_3__* dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,int,...) ; 
 int /*<<< orphan*/  BNX2X_LINK_REPORT_FD ; 
 int /*<<< orphan*/  BNX2X_LINK_REPORT_LINK_DOWN ; 
 int /*<<< orphan*/  BNX2X_LINK_REPORT_RX_FC_ON ; 
 int /*<<< orphan*/  BNX2X_LINK_REPORT_TX_FC_ON ; 
 int /*<<< orphan*/  BNX2X_MSG_IOV ; 
 int BULLETIN_ATTEMPTS ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int ETH_ALEN ; 
 int LINK_VALID ; 
 int MAC_ADDR_VALID ; 
 int PFVF_BULLETIN_CRC_ERR ; 
 int PFVF_BULLETIN_UNCHANGED ; 
 int PFVF_BULLETIN_UPDATED ; 
 int VFPF_LINK_REPORT_FULL_DUPLEX ; 
 int VFPF_LINK_REPORT_LINK_DOWN ; 
 int VFPF_LINK_REPORT_RX_FC_ON ; 
 int VFPF_LINK_REPORT_TX_FC_ON ; 
 int /*<<< orphan*/  __bnx2x_link_report (struct bnx2x*) ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ bnx2x_crc_vf_bulletin (struct pf_vf_bulletin_content*) ; 
 int /*<<< orphan*/  ether_addr_equal (struct pf_vf_bulletin_content*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,struct pf_vf_bulletin_content*,int) ; 

enum sample_bulletin_result bnx2x_sample_bulletin(struct bnx2x *bp)
{
	struct pf_vf_bulletin_content *bulletin;
	int attempts;

	/* sampling structure in mid post may result with corrupted data
	 * validate crc to ensure coherency.
	 */
	for (attempts = 0; attempts < BULLETIN_ATTEMPTS; attempts++) {
		u32 crc;

		/* sample the bulletin board */
		memcpy(&bp->shadow_bulletin, bp->pf2vf_bulletin,
		       sizeof(union pf_vf_bulletin));

		crc = bnx2x_crc_vf_bulletin(&bp->shadow_bulletin.content);

		if (bp->shadow_bulletin.content.crc == crc)
			break;

		BNX2X_ERR("bad crc on bulletin board. Contained %x computed %x\n",
			  bp->shadow_bulletin.content.crc, crc);
	}

	if (attempts >= BULLETIN_ATTEMPTS) {
		BNX2X_ERR("pf to vf bulletin board crc was wrong %d consecutive times. Aborting\n",
			  attempts);
		return PFVF_BULLETIN_CRC_ERR;
	}
	bulletin = &bp->shadow_bulletin.content;

	/* bulletin board hasn't changed since last sample */
	if (bp->old_bulletin.version == bulletin->version)
		return PFVF_BULLETIN_UNCHANGED;

	/* the mac address in bulletin board is valid and is new */
	if (bulletin->valid_bitmap & 1 << MAC_ADDR_VALID &&
	    !ether_addr_equal(bulletin->mac, bp->old_bulletin.mac)) {
		/* update new mac to net device */
		memcpy(bp->dev->dev_addr, bulletin->mac, ETH_ALEN);
	}

	if (bulletin->valid_bitmap & (1 << LINK_VALID)) {
		DP(BNX2X_MSG_IOV, "link update speed %d flags %x\n",
		   bulletin->link_speed, bulletin->link_flags);

		bp->vf_link_vars.line_speed = bulletin->link_speed;
		bp->vf_link_vars.link_report_flags = 0;
		/* Link is down */
		if (bulletin->link_flags & VFPF_LINK_REPORT_LINK_DOWN)
			__set_bit(BNX2X_LINK_REPORT_LINK_DOWN,
				  &bp->vf_link_vars.link_report_flags);
		/* Full DUPLEX */
		if (bulletin->link_flags & VFPF_LINK_REPORT_FULL_DUPLEX)
			__set_bit(BNX2X_LINK_REPORT_FD,
				  &bp->vf_link_vars.link_report_flags);
		/* Rx Flow Control is ON */
		if (bulletin->link_flags & VFPF_LINK_REPORT_RX_FC_ON)
			__set_bit(BNX2X_LINK_REPORT_RX_FC_ON,
				  &bp->vf_link_vars.link_report_flags);
		/* Tx Flow Control is ON */
		if (bulletin->link_flags & VFPF_LINK_REPORT_TX_FC_ON)
			__set_bit(BNX2X_LINK_REPORT_TX_FC_ON,
				  &bp->vf_link_vars.link_report_flags);
		__bnx2x_link_report(bp);
	}

	/* copy new bulletin board to bp */
	memcpy(&bp->old_bulletin, bulletin,
	       sizeof(struct pf_vf_bulletin_content));

	return PFVF_BULLETIN_UPDATED;
}