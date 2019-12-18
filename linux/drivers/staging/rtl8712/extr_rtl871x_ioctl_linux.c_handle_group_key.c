#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
union Keytype {int /*<<< orphan*/  skey; } ;
struct TYPE_7__ {int idx; int key_len; int /*<<< orphan*/ * key; } ;
struct TYPE_8__ {TYPE_1__ crypt; } ;
struct ieee_param {TYPE_2__ u; } ;
struct TYPE_11__ {int /*<<< orphan*/  dhcp_timer; } ;
struct TYPE_10__ {scalar_t__ pwr_mode; } ;
struct TYPE_9__ {scalar_t__ power_mgnt; } ;
struct TYPE_12__ {int binstallGrpkey; union Keytype* XGrprxmickey; union Keytype* XGrptxmickey; union Keytype* XGrpKey; } ;
struct _adapter {TYPE_5__ mlmepriv; TYPE_4__ pwrctrlpriv; TYPE_3__ registrypriv; TYPE_6__ securitypriv; } ;

/* Variables and functions */
 scalar_t__ PS_MODE_ACTIVE ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  r8712_set_key (struct _adapter*,TYPE_6__*,int) ; 

__attribute__((used)) static inline void handle_group_key(struct ieee_param *param,
				    struct _adapter *padapter)
{
	union Keytype *gk = padapter->securitypriv.XGrpKey;
	union Keytype *gtk = padapter->securitypriv.XGrptxmickey;
	union Keytype *grk = padapter->securitypriv.XGrprxmickey;

	if (param->u.crypt.idx > 0 &&
	    param->u.crypt.idx < 3) {
		/* group key idx is 1 or 2 */
		memcpy(gk[param->u.crypt.idx - 1].skey,
		       param->u.crypt.key,
		       (param->u.crypt.key_len > 16 ? 16 :
			param->u.crypt.key_len));
		memcpy(gtk[param->u.crypt.idx - 1].skey,
		       &param->u.crypt.key[16], 8);
		memcpy(grk[param->u.crypt.idx - 1].skey,
		       &param->u.crypt.key[24], 8);
		padapter->securitypriv.binstallGrpkey = true;
		r8712_set_key(padapter, &padapter->securitypriv,
			param->u.crypt.idx);
		if (padapter->registrypriv.power_mgnt > PS_MODE_ACTIVE) {
			if (padapter->registrypriv.power_mgnt !=
			    padapter->pwrctrlpriv.pwr_mode)
				mod_timer(&padapter->mlmepriv.dhcp_timer,
					  jiffies + msecs_to_jiffies(60000));
		}
	}
}