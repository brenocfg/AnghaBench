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
struct nv_swncq_port_priv {scalar_t__ ncq_flags; scalar_t__ sdbfis_bits; scalar_t__ dmafis_bits; scalar_t__ dhfis_bits; } ;
struct ata_port {struct nv_swncq_port_priv* private_data; } ;

/* Variables and functions */

__attribute__((used)) static void nv_swncq_fis_reinit(struct ata_port *ap)
{
	struct nv_swncq_port_priv *pp = ap->private_data;

	pp->dhfis_bits = 0;
	pp->dmafis_bits = 0;
	pp->sdbfis_bits = 0;
	pp->ncq_flags = 0;
}