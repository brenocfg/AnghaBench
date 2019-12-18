#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_6__ {int /*<<< orphan*/  status; } ;
struct TYPE_5__ {int /*<<< orphan*/  status; } ;
struct mvpp2_rx_desc {TYPE_3__ pp22; TYPE_2__ pp21; } ;
struct mvpp2_port {TYPE_1__* priv; } ;
struct TYPE_4__ {scalar_t__ hw_version; } ;

/* Variables and functions */
 scalar_t__ MVPP21 ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 mvpp2_rxdesc_status_get(struct mvpp2_port *port,
				   struct mvpp2_rx_desc *rx_desc)
{
	if (port->priv->hw_version == MVPP21)
		return le32_to_cpu(rx_desc->pp21.status);
	else
		return le32_to_cpu(rx_desc->pp22.status);
}