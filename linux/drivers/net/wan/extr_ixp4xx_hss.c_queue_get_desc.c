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
typedef  int u32 ;
struct port {int dummy; } ;
struct desc {int next; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int RX_DESCS ; 
 int TX_DESCS ; 
 int /*<<< orphan*/  debug_desc (int,struct desc*) ; 
 int qmgr_get_entry (unsigned int) ; 
 int rx_desc_phys (struct port*,int /*<<< orphan*/ ) ; 
 struct desc* rx_desc_ptr (struct port*,int /*<<< orphan*/ ) ; 
 int tx_desc_phys (struct port*,int /*<<< orphan*/ ) ; 
 struct desc* tx_desc_ptr (struct port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int queue_get_desc(unsigned int queue, struct port *port,
				 int is_tx)
{
	u32 phys, tab_phys, n_desc;
	struct desc *tab;

	if (!(phys = qmgr_get_entry(queue)))
		return -1;

	BUG_ON(phys & 0x1F);
	tab_phys = is_tx ? tx_desc_phys(port, 0) : rx_desc_phys(port, 0);
	tab = is_tx ? tx_desc_ptr(port, 0) : rx_desc_ptr(port, 0);
	n_desc = (phys - tab_phys) / sizeof(struct desc);
	BUG_ON(n_desc >= (is_tx ? TX_DESCS : RX_DESCS));
	debug_desc(phys, &tab[n_desc]);
	BUG_ON(tab[n_desc].next);
	return n_desc;
}