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
struct mvpp2_rfs_rule {int dummy; } ;
struct mvpp2_port {int dummy; } ;

/* Variables and functions */
 int mvpp2_port_c2_tcam_rule_add (struct mvpp2_port*,struct mvpp2_rfs_rule*) ; 

__attribute__((used)) static int mvpp2_port_c2_rfs_rule_insert(struct mvpp2_port *port,
					 struct mvpp2_rfs_rule *rule)
{
	return mvpp2_port_c2_tcam_rule_add(port, rule);
}