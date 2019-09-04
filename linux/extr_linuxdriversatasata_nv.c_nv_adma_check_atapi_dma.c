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
struct nv_adma_port_priv {int flags; } ;
struct ata_queued_cmd {TYPE_1__* ap; } ;
struct TYPE_2__ {struct nv_adma_port_priv* private_data; } ;

/* Variables and functions */
 int NV_ADMA_ATAPI_SETUP_COMPLETE ; 

__attribute__((used)) static int nv_adma_check_atapi_dma(struct ata_queued_cmd *qc)
{
	struct nv_adma_port_priv *pp = qc->ap->private_data;
	return !(pp->flags & NV_ADMA_ATAPI_SETUP_COMPLETE);
}