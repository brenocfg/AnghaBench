#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct bfa_ioc_s {int /*<<< orphan*/  port_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfa_ioc_pcifn (struct bfa_ioc_s*) ; 
 int /*<<< orphan*/  bfa_trc (struct bfa_ioc_s*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_ioc_cb_map_port(struct bfa_ioc_s *ioc)
{
	/*
	 * For crossbow, port id is same as pci function.
	 */
	ioc->port_id = bfa_ioc_pcifn(ioc);

	bfa_trc(ioc, ioc->port_id);
}