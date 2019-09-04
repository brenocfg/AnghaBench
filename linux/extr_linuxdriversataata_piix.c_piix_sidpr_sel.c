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
struct piix_host_priv {scalar_t__ sidpr; } ;
struct ata_port {int port_no; TYPE_1__* host; } ;
struct ata_link {int pmp; struct ata_port* ap; } ;
struct TYPE_2__ {struct piix_host_priv* private_data; } ;

/* Variables and functions */
 scalar_t__ PIIX_SIDPR_IDX ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int* piix_sidx_map ; 

__attribute__((used)) static void piix_sidpr_sel(struct ata_link *link, unsigned int reg)
{
	struct ata_port *ap = link->ap;
	struct piix_host_priv *hpriv = ap->host->private_data;

	iowrite32(((ap->port_no * 2 + link->pmp) << 8) | piix_sidx_map[reg],
		  hpriv->sidpr + PIIX_SIDPR_IDX);
}