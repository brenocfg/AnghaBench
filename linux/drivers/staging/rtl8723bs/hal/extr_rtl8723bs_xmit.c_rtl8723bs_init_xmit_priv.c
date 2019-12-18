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
struct xmit_priv {int /*<<< orphan*/  SdioXmitTerminate; int /*<<< orphan*/  SdioXmitStart; } ;
struct hal_com_data {int /*<<< orphan*/  SdioTxFIFOFreePageLock; } ;
struct adapter {struct xmit_priv xmitpriv; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 struct hal_com_data* GET_HAL_DATA (struct adapter*) ; 
 int /*<<< orphan*/  _SUCCESS ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

s32 rtl8723bs_init_xmit_priv(struct adapter *padapter)
{
	struct xmit_priv *xmitpriv = &padapter->xmitpriv;
	struct hal_com_data *phal;


	phal = GET_HAL_DATA(padapter);

	spin_lock_init(&phal->SdioTxFIFOFreePageLock);
	init_completion(&xmitpriv->SdioXmitStart);
	init_completion(&xmitpriv->SdioXmitTerminate);

	return _SUCCESS;
}