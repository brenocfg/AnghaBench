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
struct TYPE_3__ {int /*<<< orphan*/  coherency_required; } ;
struct TYPE_4__ {TYPE_1__ to_host; } ;
struct paace {TYPE_2__ domain_attr; int /*<<< orphan*/  addr_bitfields; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAACE_AF_PT ; 
 int /*<<< orphan*/  PAACE_DA_HOST_CR ; 
 int /*<<< orphan*/  PAACE_M_COHERENCE_REQ ; 
 int /*<<< orphan*/  PAACE_PT_SECONDARY ; 
 int /*<<< orphan*/  set_bf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pamu_init_spaace(struct paace *spaace)
{
	set_bf(spaace->addr_bitfields, PAACE_AF_PT, PAACE_PT_SECONDARY);
	set_bf(spaace->domain_attr.to_host.coherency_required, PAACE_DA_HOST_CR,
	       PAACE_M_COHERENCE_REQ);
}