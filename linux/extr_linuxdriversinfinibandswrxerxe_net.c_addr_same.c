#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ port_guid; } ;
struct rxe_dev {TYPE_1__ port; } ;
struct TYPE_6__ {scalar_t__ interface_id; } ;
struct TYPE_7__ {TYPE_2__ global; } ;
struct TYPE_8__ {TYPE_3__ dgid; } ;
struct rxe_av {TYPE_4__ grh; } ;

/* Variables and functions */

__attribute__((used)) static inline int addr_same(struct rxe_dev *rxe, struct rxe_av *av)
{
	return rxe->port.port_guid == av->grh.dgid.global.interface_id;
}