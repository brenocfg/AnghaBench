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
typedef  int u64 ;
struct TYPE_8__ {scalar_t__ local_id; } ;
struct TYPE_7__ {TYPE_2__* port; } ;
struct cm_id_private {TYPE_4__ id; TYPE_3__ av; } ;
typedef  int /*<<< orphan*/  __be64 ;
struct TYPE_6__ {TYPE_1__* mad_agent; } ;
struct TYPE_5__ {scalar_t__ hi_tid; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be64 (int) ; 

__attribute__((used)) static __be64 cm_form_tid(struct cm_id_private *cm_id_priv)
{
	u64 hi_tid, low_tid;

	hi_tid   = ((u64) cm_id_priv->av.port->mad_agent->hi_tid) << 32;
	low_tid  = (u64)cm_id_priv->id.local_id;
	return cpu_to_be64(hi_tid | low_tid);
}