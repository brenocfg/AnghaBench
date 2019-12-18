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
struct macsec_tx_sa {int dummy; } ;
struct macsec_rx_sc {int /*<<< orphan*/  next; } ;
struct TYPE_3__ {scalar_t__* sa; } ;
struct TYPE_4__ {TYPE_1__ tx_sc; scalar_t__ rx_sc; } ;
struct macsec_dev {TYPE_2__ secy; } ;

/* Variables and functions */
 int MACSEC_NUM_AN ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_tx_sa (struct macsec_tx_sa*) ; 
 int /*<<< orphan*/  free_rx_sc (struct macsec_rx_sc*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (scalar_t__,int /*<<< orphan*/ ) ; 
 void* rtnl_dereference (scalar_t__) ; 

__attribute__((used)) static void macsec_del_dev(struct macsec_dev *macsec)
{
	int i;

	while (macsec->secy.rx_sc) {
		struct macsec_rx_sc *rx_sc = rtnl_dereference(macsec->secy.rx_sc);

		rcu_assign_pointer(macsec->secy.rx_sc, rx_sc->next);
		free_rx_sc(rx_sc);
	}

	for (i = 0; i < MACSEC_NUM_AN; i++) {
		struct macsec_tx_sa *sa = rtnl_dereference(macsec->secy.tx_sc.sa[i]);

		if (sa) {
			RCU_INIT_POINTER(macsec->secy.tx_sc.sa[i], NULL);
			clear_tx_sa(sa);
		}
	}
}