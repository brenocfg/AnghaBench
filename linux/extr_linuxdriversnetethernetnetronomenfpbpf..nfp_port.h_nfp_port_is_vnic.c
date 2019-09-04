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
struct nfp_port {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ NFP_PORT_PF_PORT ; 
 scalar_t__ NFP_PORT_VF_PORT ; 

__attribute__((used)) static inline bool nfp_port_is_vnic(const struct nfp_port *port)
{
	return port->type == NFP_PORT_PF_PORT || port->type == NFP_PORT_VF_PORT;
}