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
struct TYPE_2__ {scalar_t__ status; } ;
struct ib_dm_mad {TYPE_1__ mad_hdr; scalar_t__ data; } ;
struct ib_class_port_info {int base_version; int class_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_set_cpi_resp_time (struct ib_class_port_info*,int) ; 
 int /*<<< orphan*/  memset (struct ib_class_port_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void srpt_get_class_port_info(struct ib_dm_mad *mad)
{
	struct ib_class_port_info *cif;

	cif = (struct ib_class_port_info *)mad->data;
	memset(cif, 0, sizeof(*cif));
	cif->base_version = 1;
	cif->class_version = 1;

	ib_set_cpi_resp_time(cif, 20);
	mad->mad_hdr.status = 0;
}