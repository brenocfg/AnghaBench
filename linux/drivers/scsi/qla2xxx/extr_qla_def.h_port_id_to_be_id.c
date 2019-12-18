#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  al_pa; int /*<<< orphan*/  area; int /*<<< orphan*/  domain; } ;
struct TYPE_7__ {TYPE_1__ b; } ;
typedef  TYPE_2__ port_id_t ;
struct TYPE_8__ {int /*<<< orphan*/  al_pa; int /*<<< orphan*/  area; int /*<<< orphan*/  domain; } ;
typedef  TYPE_3__ be_id_t ;

/* Variables and functions */

__attribute__((used)) static inline be_id_t port_id_to_be_id(port_id_t port_id)
{
	be_id_t res;

	res.domain = port_id.b.domain;
	res.area   = port_id.b.area;
	res.al_pa  = port_id.b.al_pa;

	return res;
}