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
typedef  int u8 ;
struct drm_dp_mst_port {int port_num; TYPE_1__* parent; } ;
struct TYPE_2__ {int lct; int /*<<< orphan*/  rad; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u8 drm_dp_calculate_rad(struct drm_dp_mst_port *port,
				 u8 *rad)
{
	int parent_lct = port->parent->lct;
	int shift = 4;
	int idx = (parent_lct - 1) / 2;
	if (parent_lct > 1) {
		memcpy(rad, port->parent->rad, idx + 1);
		shift = (parent_lct % 2) ? 4 : 0;
	} else
		rad[0] = 0;

	rad[idx] |= port->port_num << shift;
	return parent_lct + 1;
}