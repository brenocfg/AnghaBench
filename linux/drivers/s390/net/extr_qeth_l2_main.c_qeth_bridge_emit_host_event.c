#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct qeth_card {TYPE_2__* gdev; } ;
struct net_if_token {int cssid; int ssid; int devnum; int iid; int chpid; int chid; } ;
struct mac_addr_lnid {int lnid; int /*<<< orphan*/  mac; } ;
typedef  int /*<<< orphan*/  str ;
typedef  enum qeth_an_event_type { ____Placeholder_qeth_an_event_type } qeth_an_event_type ;
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int IPA_ADDR_CHANGE_CODE_MACADDR ; 
 int IPA_ADDR_CHANGE_CODE_REMOVAL ; 
 int IPA_ADDR_CHANGE_CODE_VLANID ; 
 int /*<<< orphan*/  KOBJ_CHANGE ; 
#define  anev_abort 130 
#define  anev_reg_unreg 129 
#define  anev_reset 128 
 int /*<<< orphan*/  kobject_uevent_env (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 

__attribute__((used)) static void qeth_bridge_emit_host_event(struct qeth_card *card,
	enum qeth_an_event_type evtype,
	u8 code, struct net_if_token *token, struct mac_addr_lnid *addr_lnid)
{
	char str[7][32];
	char *env[8];
	int i = 0;

	switch (evtype) {
	case anev_reg_unreg:
		snprintf(str[i], sizeof(str[i]), "BRIDGEDHOST=%s",
				(code & IPA_ADDR_CHANGE_CODE_REMOVAL)
				? "deregister" : "register");
		env[i] = str[i]; i++;
		if (code & IPA_ADDR_CHANGE_CODE_VLANID) {
			snprintf(str[i], sizeof(str[i]), "VLAN=%d",
				addr_lnid->lnid);
			env[i] = str[i]; i++;
		}
		if (code & IPA_ADDR_CHANGE_CODE_MACADDR) {
			snprintf(str[i], sizeof(str[i]), "MAC=%pM",
				addr_lnid->mac);
			env[i] = str[i]; i++;
		}
		snprintf(str[i], sizeof(str[i]), "NTOK_BUSID=%x.%x.%04x",
			token->cssid, token->ssid, token->devnum);
		env[i] = str[i]; i++;
		snprintf(str[i], sizeof(str[i]), "NTOK_IID=%02x", token->iid);
		env[i] = str[i]; i++;
		snprintf(str[i], sizeof(str[i]), "NTOK_CHPID=%02x",
				token->chpid);
		env[i] = str[i]; i++;
		snprintf(str[i], sizeof(str[i]), "NTOK_CHID=%04x", token->chid);
		env[i] = str[i]; i++;
		break;
	case anev_abort:
		snprintf(str[i], sizeof(str[i]), "BRIDGEDHOST=abort");
		env[i] = str[i]; i++;
		break;
	case anev_reset:
		snprintf(str[i], sizeof(str[i]), "BRIDGEDHOST=reset");
		env[i] = str[i]; i++;
		break;
	}
	env[i] = NULL;
	kobject_uevent_env(&card->gdev->dev.kobj, KOBJ_CHANGE, env);
}