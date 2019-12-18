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
typedef  union recv_frame {int dummy; } recv_frame ;
struct ht_priv {int ht_option; } ;
struct mlme_priv {struct ht_priv htpriv; } ;
struct _adapter {int /*<<< orphan*/  surprise_removed; int /*<<< orphan*/  driver_stopped; struct mlme_priv mlmepriv; } ;

/* Variables and functions */
 int _FAIL ; 
 int _SUCCESS ; 
 int /*<<< orphan*/  r8712_recv_indicatepkt (struct _adapter*,union recv_frame*) ; 
 int r8712_wlanhdr_to_ethhdr (union recv_frame*) ; 
 scalar_t__ recv_indicatepkt_reorder (struct _adapter*,union recv_frame*) ; 

__attribute__((used)) static int r8712_process_recv_indicatepkts(struct _adapter *padapter,
			      union recv_frame *prframe)
{
	int retval = _SUCCESS;
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;
	struct ht_priv	*phtpriv = &pmlmepriv->htpriv;

	if (phtpriv->ht_option == 1) { /*B/G/N Mode*/
		if (recv_indicatepkt_reorder(padapter, prframe)) {
			/* including perform A-MPDU Rx Ordering Buffer Control*/
			if (!padapter->driver_stopped &&
			    !padapter->surprise_removed)
				return _FAIL;
		}
	} else { /*B/G mode*/
		retval = r8712_wlanhdr_to_ethhdr(prframe);
		if (retval)
			return _FAIL;
		if (!padapter->driver_stopped && !padapter->surprise_removed) {
			/* indicate this recv_frame */
			r8712_recv_indicatepkt(padapter, prframe);
		} else {
			return _FAIL;
		}
	}
	return retval;
}