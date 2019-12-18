#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct qeth_reply {int dummy; } ;
struct TYPE_2__ {int return_code; } ;
struct qeth_ipa_cmd {TYPE_1__ hdr; } ;
struct qeth_card {int dummy; } ;

/* Variables and functions */
 int EADDRINUSE ; 
 int EIO ; 
 int ENETDOWN ; 
 int ENOENT ; 
#define  IPA_RC_DUPLICATE_IP_ADDRESS 131 
#define  IPA_RC_LAN_OFFLINE 130 
#define  IPA_RC_MC_ADDR_NOT_FOUND 129 
#define  IPA_RC_SUCCESS 128 

__attribute__((used)) static int qeth_l3_setdelip_cb(struct qeth_card *card, struct qeth_reply *reply,
			       unsigned long data)
{
	struct qeth_ipa_cmd *cmd = (struct qeth_ipa_cmd *) data;

	switch (cmd->hdr.return_code) {
	case IPA_RC_SUCCESS:
		return 0;
	case IPA_RC_DUPLICATE_IP_ADDRESS:
		return -EADDRINUSE;
	case IPA_RC_MC_ADDR_NOT_FOUND:
		return -ENOENT;
	case IPA_RC_LAN_OFFLINE:
		return -ENETDOWN;
	default:
		return -EIO;
	}
}