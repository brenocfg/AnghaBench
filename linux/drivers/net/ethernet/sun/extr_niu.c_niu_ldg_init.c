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
struct niu_parent {scalar_t__ plat_type; int* rxchan_per_port; int* txchan_per_port; } ;
struct niu_ldg {int ldg_num; int timer; struct niu* np; int /*<<< orphan*/  napi; int /*<<< orphan*/  irq; } ;
struct niu {int num_ldg; int port; struct niu_parent* parent; TYPE_1__* dev; struct niu_ldg* ldg; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDN_DEVICE_ERROR ; 
 int /*<<< orphan*/  LDN_MAC (int) ; 
 int /*<<< orphan*/  LDN_MIF ; 
 int /*<<< orphan*/  LDN_RXDMA (int) ; 
 int /*<<< orphan*/  LDN_TXDMA (int) ; 
 int NIU_NUM_LDG ; 
 scalar_t__ PLAT_TYPE_NIU ; 
 int /*<<< orphan*/  netif_napi_add (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int niu_ldg_assign_ldn (struct niu*,struct niu_parent*,int,int /*<<< orphan*/ ) ; 
 int niu_n2_irq_init (struct niu*,int*) ; 
 int /*<<< orphan*/  niu_poll ; 
 int niu_set_ldg_sid (struct niu*,int,int,int) ; 
 int /*<<< orphan*/  niu_try_msix (struct niu*,int*) ; 

__attribute__((used)) static int niu_ldg_init(struct niu *np)
{
	struct niu_parent *parent = np->parent;
	u8 ldg_num_map[NIU_NUM_LDG];
	int first_chan, num_chan;
	int i, err, ldg_rotor;
	u8 port;

	np->num_ldg = 1;
	np->ldg[0].irq = np->dev->irq;
	if (parent->plat_type == PLAT_TYPE_NIU) {
		err = niu_n2_irq_init(np, ldg_num_map);
		if (err)
			return err;
	} else
		niu_try_msix(np, ldg_num_map);

	port = np->port;
	for (i = 0; i < np->num_ldg; i++) {
		struct niu_ldg *lp = &np->ldg[i];

		netif_napi_add(np->dev, &lp->napi, niu_poll, 64);

		lp->np = np;
		lp->ldg_num = ldg_num_map[i];
		lp->timer = 2; /* XXX */

		/* On N2 NIU the firmware has setup the SID mappings so they go
		 * to the correct values that will route the LDG to the proper
		 * interrupt in the NCU interrupt table.
		 */
		if (np->parent->plat_type != PLAT_TYPE_NIU) {
			err = niu_set_ldg_sid(np, lp->ldg_num, port, i);
			if (err)
				return err;
		}
	}

	/* We adopt the LDG assignment ordering used by the N2 NIU
	 * 'interrupt' properties because that simplifies a lot of
	 * things.  This ordering is:
	 *
	 *	MAC
	 *	MIF	(if port zero)
	 *	SYSERR	(if port zero)
	 *	RX channels
	 *	TX channels
	 */

	ldg_rotor = 0;

	err = niu_ldg_assign_ldn(np, parent, ldg_num_map[ldg_rotor],
				  LDN_MAC(port));
	if (err)
		return err;

	ldg_rotor++;
	if (ldg_rotor == np->num_ldg)
		ldg_rotor = 0;

	if (port == 0) {
		err = niu_ldg_assign_ldn(np, parent,
					 ldg_num_map[ldg_rotor],
					 LDN_MIF);
		if (err)
			return err;

		ldg_rotor++;
		if (ldg_rotor == np->num_ldg)
			ldg_rotor = 0;

		err = niu_ldg_assign_ldn(np, parent,
					 ldg_num_map[ldg_rotor],
					 LDN_DEVICE_ERROR);
		if (err)
			return err;

		ldg_rotor++;
		if (ldg_rotor == np->num_ldg)
			ldg_rotor = 0;

	}

	first_chan = 0;
	for (i = 0; i < port; i++)
		first_chan += parent->rxchan_per_port[i];
	num_chan = parent->rxchan_per_port[port];

	for (i = first_chan; i < (first_chan + num_chan); i++) {
		err = niu_ldg_assign_ldn(np, parent,
					 ldg_num_map[ldg_rotor],
					 LDN_RXDMA(i));
		if (err)
			return err;
		ldg_rotor++;
		if (ldg_rotor == np->num_ldg)
			ldg_rotor = 0;
	}

	first_chan = 0;
	for (i = 0; i < port; i++)
		first_chan += parent->txchan_per_port[i];
	num_chan = parent->txchan_per_port[port];
	for (i = first_chan; i < (first_chan + num_chan); i++) {
		err = niu_ldg_assign_ldn(np, parent,
					 ldg_num_map[ldg_rotor],
					 LDN_TXDMA(i));
		if (err)
			return err;
		ldg_rotor++;
		if (ldg_rotor == np->num_ldg)
			ldg_rotor = 0;
	}

	return 0;
}