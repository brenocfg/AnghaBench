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
struct qtnf_bus {int fw_state; } ;
typedef  enum qtnf_fw_state { ____Placeholder_qtnf_fw_state } qtnf_fw_state ;

/* Variables and functions */
 int QTNF_FW_STATE_ACTIVE ; 
 int QTNF_FW_STATE_DEAD ; 
 int QTNF_FW_STATE_RUNNING ; 

__attribute__((used)) static inline bool qtnf_fw_is_attached(struct qtnf_bus *bus)
{
	enum qtnf_fw_state state = bus->fw_state;

	return ((state == QTNF_FW_STATE_ACTIVE) ||
		(state == QTNF_FW_STATE_RUNNING) ||
		(state == QTNF_FW_STATE_DEAD));
}