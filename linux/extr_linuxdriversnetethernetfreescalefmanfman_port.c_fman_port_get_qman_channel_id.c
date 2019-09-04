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
struct TYPE_2__ {int /*<<< orphan*/  qman_channel_id; } ;
struct fman_port {TYPE_1__ dts_params; } ;

/* Variables and functions */

u32 fman_port_get_qman_channel_id(struct fman_port *port)
{
	return port->dts_params.qman_channel_id;
}