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
struct net_device {int dummy; } ;
struct fcoe_port {scalar_t__ priv; } ;
struct fc_lport {int dummy; } ;
struct bnx2fc_interface {struct net_device* netdev; } ;

/* Variables and functions */
 scalar_t__ lport_priv (struct fc_lport const*) ; 

__attribute__((used)) static inline struct net_device *bnx2fc_netdev(const struct fc_lport *lport)
{
	return ((struct bnx2fc_interface *)
		((struct fcoe_port *)lport_priv(lport))->priv)->netdev;
}