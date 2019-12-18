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
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct mlme_ext_info {scalar_t__ preamble_mode; scalar_t__ slotTime; } ;
struct mlme_ext_priv {int cur_wireless_mode; struct mlme_ext_info mlmext_info; } ;
struct adapter {struct mlme_ext_priv mlmeextpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  HW_VAR_ACK_PREAMBLE ; 
 int /*<<< orphan*/  HW_VAR_SLOT_TIME ; 
 scalar_t__ NON_SHORT_SLOT_TIME ; 
 scalar_t__ PREAMBLE_LONG ; 
 scalar_t__ PREAMBLE_SHORT ; 
 scalar_t__ SHORT_SLOT_TIME ; 
 int WIRELESS_11A ; 
 int WIRELESS_11G ; 
 int WIRELESS_11_24N ; 
 int WIRELESS_11_5N ; 
 int cIBSS ; 
 int cShortPreamble ; 
 int cShortSlotTime ; 
 int /*<<< orphan*/  rtw_hal_set_hwreg (struct adapter*,int /*<<< orphan*/ ,scalar_t__*) ; 

void update_capinfo(struct adapter *Adapter, u16 updateCap)
{
	struct mlme_ext_priv *pmlmeext = &Adapter->mlmeextpriv;
	struct mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	bool ShortPreamble;

	/*  Check preamble mode, 2005.01.06, by rcnjko. */
	/*  Mark to update preamble value forever, 2008.03.18 by lanhsin */

	if (updateCap & cShortPreamble) { /*  Short Preamble */
		if (pmlmeinfo->preamble_mode != PREAMBLE_SHORT) { /*  PREAMBLE_LONG or PREAMBLE_AUTO */
			ShortPreamble = true;
			pmlmeinfo->preamble_mode = PREAMBLE_SHORT;
			rtw_hal_set_hwreg(Adapter, HW_VAR_ACK_PREAMBLE, (u8 *)&ShortPreamble);
		}
	} else { /*  Long Preamble */
		if (pmlmeinfo->preamble_mode != PREAMBLE_LONG) {  /*  PREAMBLE_SHORT or PREAMBLE_AUTO */
			ShortPreamble = false;
			pmlmeinfo->preamble_mode = PREAMBLE_LONG;
			rtw_hal_set_hwreg(Adapter, HW_VAR_ACK_PREAMBLE, (u8 *)&ShortPreamble);
		}
	}

	if (updateCap & cIBSS) {
		/* Filen: See 802.11-2007 p.91 */
		pmlmeinfo->slotTime = NON_SHORT_SLOT_TIME;
	} else { /* Filen: See 802.11-2007 p.90 */
		if (pmlmeext->cur_wireless_mode & (WIRELESS_11G | WIRELESS_11_24N)) {
			if (updateCap & cShortSlotTime) { /*  Short Slot Time */
				if (pmlmeinfo->slotTime != SHORT_SLOT_TIME)
					pmlmeinfo->slotTime = SHORT_SLOT_TIME;
			} else { /*  Long Slot Time */
				if (pmlmeinfo->slotTime != NON_SHORT_SLOT_TIME)
					pmlmeinfo->slotTime = NON_SHORT_SLOT_TIME;
			}
		} else if (pmlmeext->cur_wireless_mode & (WIRELESS_11A | WIRELESS_11_5N)) {
			pmlmeinfo->slotTime = SHORT_SLOT_TIME;
		} else {
			/* B Mode */
			pmlmeinfo->slotTime = NON_SHORT_SLOT_TIME;
		}
	}

	rtw_hal_set_hwreg(Adapter, HW_VAR_SLOT_TIME, &pmlmeinfo->slotTime);
}