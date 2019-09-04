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
struct net_device {scalar_t__ base_addr; } ;
struct Am79C960 {int RDP; int /*<<< orphan*/  RAP; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR0 ; 
 int INEA ; 
 int STOP ; 
 int STRT ; 
 int /*<<< orphan*/  ariadne_init_ring (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 

__attribute__((used)) static inline void ariadne_reset(struct net_device *dev)
{
	volatile struct Am79C960 *lance = (struct Am79C960 *)dev->base_addr;

	lance->RAP = CSR0;	/* PCnet-ISA Controller Status */
	lance->RDP = STOP;
	ariadne_init_ring(dev);
	lance->RDP = INEA | STRT;
	netif_start_queue(dev);
}