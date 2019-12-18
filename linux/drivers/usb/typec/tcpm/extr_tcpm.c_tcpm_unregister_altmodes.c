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
struct pd_mode_data {int altmodes; } ;
struct tcpm_port {int /*<<< orphan*/ ** partner_altmode; struct pd_mode_data mode_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct pd_mode_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  typec_unregister_altmode (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tcpm_unregister_altmodes(struct tcpm_port *port)
{
	struct pd_mode_data *modep = &port->mode_data;
	int i;

	for (i = 0; i < modep->altmodes; i++) {
		typec_unregister_altmode(port->partner_altmode[i]);
		port->partner_altmode[i] = NULL;
	}

	memset(modep, 0, sizeof(*modep));
}