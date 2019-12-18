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
typedef  int u8 ;
struct sta_info {int /*<<< orphan*/  dot118021x_UncstKey; int /*<<< orphan*/ * hwaddr; } ;
struct set_stakey_rsp {int dummy; } ;
struct set_stakey_parm {unsigned char algorithm; int* rsp; int rspsz; int /*<<< orphan*/  key; int /*<<< orphan*/ * addr; } ;
struct security_priv {size_t dot118021XGrpKeyid; int busetkipkey; TYPE_1__* dot118021XGrpKey; scalar_t__ dot11PrivacyAlgrthm; } ;
struct mlme_priv {int dummy; } ;
struct cmd_priv {int dummy; } ;
struct cmd_obj {unsigned char algorithm; int* rsp; int rspsz; int /*<<< orphan*/  key; int /*<<< orphan*/ * addr; } ;
struct adapter {struct security_priv securitypriv; struct mlme_priv mlmepriv; struct cmd_priv cmdpriv; } ;
struct TYPE_2__ {int /*<<< orphan*/  skey; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  GET_ENCRY_ALGO (struct security_priv*,struct sta_info*,unsigned char,int) ; 
 int /*<<< orphan*/  WIFI_STATION_STATE ; 
 int _FAIL ; 
 int _SUCCESS ; 
 int /*<<< orphan*/  _SetStaKey_CMD_ ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_h2fwcmd_w_parm_no_rsp (struct set_stakey_parm*,struct set_stakey_parm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct set_stakey_parm*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int rtw_enqueue_cmd (struct cmd_priv*,struct set_stakey_parm*) ; 
 void* rtw_zmalloc (int) ; 
 int /*<<< orphan*/  set_stakey_hdl (struct adapter*,int*) ; 

u8 rtw_setstakey_cmd(struct adapter *padapter, struct sta_info *sta, u8 unicast_key, bool enqueue)
{
	struct cmd_obj *ph2c;
	struct set_stakey_parm	*psetstakey_para;
	struct cmd_priv 			*pcmdpriv = &padapter->cmdpriv;
	struct set_stakey_rsp		*psetstakey_rsp = NULL;

	struct mlme_priv 		*pmlmepriv = &padapter->mlmepriv;
	struct security_priv 	*psecuritypriv = &padapter->securitypriv;
	u8 res = _SUCCESS;

	psetstakey_para = rtw_zmalloc(sizeof(struct set_stakey_parm));
	if (psetstakey_para == NULL) {
		res = _FAIL;
		goto exit;
	}

	memcpy(psetstakey_para->addr, sta->hwaddr, ETH_ALEN);

	if (check_fwstate(pmlmepriv, WIFI_STATION_STATE)) {
		psetstakey_para->algorithm = (unsigned char) psecuritypriv->dot11PrivacyAlgrthm;
	} else {
		GET_ENCRY_ALGO(psecuritypriv, sta, psetstakey_para->algorithm, false);
	}

	if (unicast_key == true) {
		memcpy(&psetstakey_para->key, &sta->dot118021x_UncstKey, 16);
	} else {
		memcpy(&psetstakey_para->key, &psecuritypriv->dot118021XGrpKey[psecuritypriv->dot118021XGrpKeyid].skey, 16);
	}

	/* jeff: set this becasue at least sw key is ready */
	padapter->securitypriv.busetkipkey = true;

	if (enqueue) {
		ph2c = rtw_zmalloc(sizeof(struct cmd_obj));
		if (ph2c == NULL) {
			kfree(psetstakey_para);
			res = _FAIL;
			goto exit;
		}

		psetstakey_rsp = rtw_zmalloc(sizeof(struct set_stakey_rsp));
		if (psetstakey_rsp == NULL) {
			kfree(ph2c);
			kfree(psetstakey_para);
			res = _FAIL;
			goto exit;
		}

		init_h2fwcmd_w_parm_no_rsp(ph2c, psetstakey_para, _SetStaKey_CMD_);
		ph2c->rsp = (u8 *) psetstakey_rsp;
		ph2c->rspsz = sizeof(struct set_stakey_rsp);
		res = rtw_enqueue_cmd(pcmdpriv, ph2c);
	} else {
		set_stakey_hdl(padapter, (u8 *)psetstakey_para);
		kfree(psetstakey_para);
	}
exit:
	return res;
}