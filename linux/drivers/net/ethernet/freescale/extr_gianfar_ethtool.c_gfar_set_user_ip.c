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
struct filer_table {int dummy; } ;
struct ethtool_usrip4_spec {int /*<<< orphan*/  l4_4_bytes; int /*<<< orphan*/  proto; int /*<<< orphan*/  tos; int /*<<< orphan*/  ip4dst; int /*<<< orphan*/  ip4src; } ;

/* Variables and functions */
 int /*<<< orphan*/  RQFCR_PID_ARB ; 
 int /*<<< orphan*/  RQFCR_PID_DIA ; 
 int /*<<< orphan*/  RQFCR_PID_L4P ; 
 int /*<<< orphan*/  RQFCR_PID_SIA ; 
 int /*<<< orphan*/  RQFCR_PID_TOS ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfar_set_attribute (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct filer_table*) ; 

__attribute__((used)) static void gfar_set_user_ip(struct ethtool_usrip4_spec *value,
			     struct ethtool_usrip4_spec *mask,
			     struct filer_table *tab)
{
	gfar_set_attribute(be32_to_cpu(value->ip4src),
			   be32_to_cpu(mask->ip4src),
			   RQFCR_PID_SIA, tab);
	gfar_set_attribute(be32_to_cpu(value->ip4dst),
			   be32_to_cpu(mask->ip4dst),
			   RQFCR_PID_DIA, tab);
	gfar_set_attribute(value->tos, mask->tos, RQFCR_PID_TOS, tab);
	gfar_set_attribute(value->proto, mask->proto, RQFCR_PID_L4P, tab);
	gfar_set_attribute(be32_to_cpu(value->l4_4_bytes),
			   be32_to_cpu(mask->l4_4_bytes),
			   RQFCR_PID_ARB, tab);

}