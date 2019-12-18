#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct bfad_port_s {int dummy; } ;
struct bfa_fcs_itnim_s {TYPE_2__* rport; } ;
struct TYPE_4__ {TYPE_1__* port; } ;
struct TYPE_3__ {struct bfad_port_s* bfad_port; } ;

/* Variables and functions */

__attribute__((used)) static inline struct bfad_port_s *
bfa_fcs_itnim_get_drvport(struct bfa_fcs_itnim_s *itnim)
{
	return itnim->rport->port->bfad_port;
}