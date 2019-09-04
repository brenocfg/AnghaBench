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
struct vas_tx_win_attr {int rej_no_credit; int rx_wcred_mode; int tx_wcred_mode; int rx_win_ord_mode; int tx_win_ord_mode; int user_win; } ;
typedef  enum vas_cop_type { ____Placeholder_vas_cop_type } vas_cop_type ;

/* Variables and functions */
 int VAS_COP_TYPE_842 ; 
 int VAS_COP_TYPE_842_HIPRI ; 
 int VAS_COP_TYPE_FTW ; 
 int /*<<< orphan*/  memset (struct vas_tx_win_attr*,int /*<<< orphan*/ ,int) ; 

void vas_init_tx_win_attr(struct vas_tx_win_attr *txattr, enum vas_cop_type cop)
{
	memset(txattr, 0, sizeof(*txattr));

	if (cop == VAS_COP_TYPE_842 || cop == VAS_COP_TYPE_842_HIPRI) {
		txattr->rej_no_credit = false;
		txattr->rx_wcred_mode = true;
		txattr->tx_wcred_mode = true;
		txattr->rx_win_ord_mode = true;
		txattr->tx_win_ord_mode = true;
	} else if (cop == VAS_COP_TYPE_FTW) {
		txattr->user_win = true;
	}
}