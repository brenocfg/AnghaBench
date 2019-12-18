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
struct TYPE_6__ {int /*<<< orphan*/  SsidLength; } ;
struct wlan_bssid_ex {TYPE_3__ Ssid; int /*<<< orphan*/  IELength; int /*<<< orphan*/  Length; } ;
struct cmd_priv {int dummy; } ;
struct cmd_obj {unsigned char* parmbuf; int /*<<< orphan*/  cmdsz; scalar_t__ rspsz; int /*<<< orphan*/ * rsp; int /*<<< orphan*/  cmdcode; int /*<<< orphan*/  list; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* LedControlHandler ) (struct _adapter*,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {struct wlan_bssid_ex dev_network; } ;
struct _adapter {TYPE_2__ ledpriv; TYPE_1__ registrypriv; struct cmd_priv cmdpriv; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LED_CTL_START_TO_LINK ; 
 int /*<<< orphan*/  _CreateBss_CMD_ ; 
 struct cmd_obj* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8712_enqueue_cmd (struct cmd_priv*,struct cmd_obj*) ; 
 int /*<<< orphan*/  r8712_get_wlan_bssid_ex_sz (struct wlan_bssid_ex*) ; 
 int /*<<< orphan*/  stub1 (struct _adapter*,int /*<<< orphan*/ ) ; 

int r8712_createbss_cmd(struct _adapter *padapter)
{
	struct cmd_obj *pcmd;
	struct cmd_priv *pcmdpriv = &padapter->cmdpriv;
	struct wlan_bssid_ex *pdev_network =
				 &padapter->registrypriv.dev_network;

	padapter->ledpriv.LedControlHandler(padapter, LED_CTL_START_TO_LINK);
	pcmd = kmalloc(sizeof(*pcmd), GFP_ATOMIC);
	if (!pcmd)
		return -ENOMEM;
	INIT_LIST_HEAD(&pcmd->list);
	pcmd->cmdcode = _CreateBss_CMD_;
	pcmd->parmbuf = (unsigned char *)pdev_network;
	pcmd->cmdsz = r8712_get_wlan_bssid_ex_sz(pdev_network);
	pcmd->rsp = NULL;
	pcmd->rspsz = 0;
	/* notes: translate IELength & Length after assign to cmdsz; */
	pdev_network->Length = pcmd->cmdsz;
	pdev_network->IELength = pdev_network->IELength;
	pdev_network->Ssid.SsidLength =	pdev_network->Ssid.SsidLength;
	r8712_enqueue_cmd(pcmdpriv, pcmd);
	return 0;
}