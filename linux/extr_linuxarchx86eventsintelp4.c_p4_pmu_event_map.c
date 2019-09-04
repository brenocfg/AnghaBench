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
typedef  int /*<<< orphan*/  u64 ;
struct p4_event_bind {int /*<<< orphan*/  opcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  P4_CCCR_ESEL (unsigned int) ; 
 unsigned int P4_OPCODE_ESEL (int /*<<< orphan*/ ) ; 
 struct p4_event_bind* p4_config_get_bind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p4_config_pack_cccr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * p4_general_events ; 

__attribute__((used)) static u64 p4_pmu_event_map(int hw_event)
{
	struct p4_event_bind *bind;
	unsigned int esel;
	u64 config;

	config = p4_general_events[hw_event];
	bind = p4_config_get_bind(config);
	esel = P4_OPCODE_ESEL(bind->opcode);
	config |= p4_config_pack_cccr(P4_CCCR_ESEL(esel));

	return config;
}