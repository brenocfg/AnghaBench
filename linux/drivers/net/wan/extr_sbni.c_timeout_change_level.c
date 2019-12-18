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
struct TYPE_2__ {int /*<<< orphan*/  rxl; } ;
struct net_local {size_t cur_rxl_index; size_t timeout_rxl; scalar_t__ cur_rxl_rcvd; scalar_t__ prev_rxl_rcvd; TYPE_1__ csr1; } ;
struct net_device {scalar_t__ base_addr; } ;

/* Variables and functions */
 scalar_t__ CSR0 ; 
 scalar_t__ CSR1 ; 
 int /*<<< orphan*/  inb (scalar_t__) ; 
 struct net_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  outb (unsigned char,scalar_t__) ; 
 int /*<<< orphan*/ * rxl_tab ; 
 size_t* timeout_rxl_tab ; 

__attribute__((used)) static void
timeout_change_level( struct net_device  *dev )
{
	struct net_local  *nl = netdev_priv(dev);

	nl->cur_rxl_index = timeout_rxl_tab[ nl->timeout_rxl ];
	if( ++nl->timeout_rxl >= 4 )
		nl->timeout_rxl = 0;

	nl->csr1.rxl = rxl_tab[ nl->cur_rxl_index ];
	inb( dev->base_addr + CSR0 );
	outb( *(unsigned char *)&nl->csr1, dev->base_addr + CSR1 );

	nl->prev_rxl_rcvd = nl->cur_rxl_rcvd;
	nl->cur_rxl_rcvd  = 0;
}