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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {scalar_t__ bad_pkey_cntr; } ;
struct rxe_port {int /*<<< orphan*/  port_lock; TYPE_1__ attr; } ;

/* Variables and functions */
 scalar_t__ min (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void set_bad_pkey_cntr(struct rxe_port *port)
{
	spin_lock_bh(&port->port_lock);
	port->attr.bad_pkey_cntr = min((u32)0xffff,
				       port->attr.bad_pkey_cntr + 1);
	spin_unlock_bh(&port->port_lock);
}