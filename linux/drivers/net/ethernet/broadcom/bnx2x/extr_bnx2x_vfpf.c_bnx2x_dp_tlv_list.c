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
struct channel_tlv {scalar_t__ type; int /*<<< orphan*/  length; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_MSG_IOV ; 
 scalar_t__ CHANNEL_TLV_LIST_END ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int MAX_TLVS_IN_LIST ; 
 int /*<<< orphan*/  WARN (int,char*) ; 

__attribute__((used)) static void bnx2x_dp_tlv_list(struct bnx2x *bp, void *tlvs_list)
{
	int i = 1;
	struct channel_tlv *tlv = (struct channel_tlv *)tlvs_list;

	while (tlv->type != CHANNEL_TLV_LIST_END) {
		/* output tlv */
		DP(BNX2X_MSG_IOV, "TLV number %d: type %d, length %d\n", i,
		   tlv->type, tlv->length);

		/* advance to next tlv */
		tlvs_list += tlv->length;

		/* cast general tlv list pointer to channel tlv header*/
		tlv = (struct channel_tlv *)tlvs_list;

		i++;

		/* break condition for this loop */
		if (i > MAX_TLVS_IN_LIST) {
			WARN(true, "corrupt tlvs");
			return;
		}
	}

	/* output last tlv */
	DP(BNX2X_MSG_IOV, "TLV number %d: type %d, length %d\n", i,
	   tlv->type, tlv->length);
}