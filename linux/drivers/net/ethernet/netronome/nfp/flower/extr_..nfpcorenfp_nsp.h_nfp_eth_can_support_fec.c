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
struct nfp_eth_table_port {int /*<<< orphan*/  fec_modes_supported; } ;

/* Variables and functions */

__attribute__((used)) static inline bool nfp_eth_can_support_fec(struct nfp_eth_table_port *eth_port)
{
	return !!eth_port->fec_modes_supported;
}