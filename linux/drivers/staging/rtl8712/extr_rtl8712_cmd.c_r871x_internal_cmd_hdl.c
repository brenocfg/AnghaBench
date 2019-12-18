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
typedef  int /*<<< orphan*/  u8 ;
struct drvint_cmd_parm {int i_cid; int /*<<< orphan*/  pbuf; } ;
struct _adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  StatusWatchdogCallback (struct _adapter*) ; 
#define  WDG_WK_CID 128 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void r871x_internal_cmd_hdl(struct _adapter *padapter, u8 *pbuf)
{
	struct drvint_cmd_parm *pdrvcmd;

	if (!pbuf)
		return;
	pdrvcmd = (struct drvint_cmd_parm *)pbuf;
	switch (pdrvcmd->i_cid) {
	case WDG_WK_CID:
		StatusWatchdogCallback(padapter);
		break;
	default:
		break;
	}
	kfree(pdrvcmd->pbuf);
}