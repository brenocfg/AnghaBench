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
typedef  int /*<<< orphan*/  u16 ;
struct nvmet_port {int* ana_state; } ;
struct nvmet_ns {size_t anagrpid; } ;
typedef  enum nvme_ana_state { ____Placeholder_nvme_ana_state } nvme_ana_state ;

/* Variables and functions */
 int NVME_ANA_CHANGE ; 
 int NVME_ANA_INACCESSIBLE ; 
 int NVME_ANA_PERSISTENT_LOSS ; 
 int /*<<< orphan*/  NVME_SC_ANA_INACCESSIBLE ; 
 int /*<<< orphan*/  NVME_SC_ANA_PERSISTENT_LOSS ; 
 int /*<<< orphan*/  NVME_SC_ANA_TRANSITION ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline u16 nvmet_check_ana_state(struct nvmet_port *port,
		struct nvmet_ns *ns)
{
	enum nvme_ana_state state = port->ana_state[ns->anagrpid];

	if (unlikely(state == NVME_ANA_INACCESSIBLE))
		return NVME_SC_ANA_INACCESSIBLE;
	if (unlikely(state == NVME_ANA_PERSISTENT_LOSS))
		return NVME_SC_ANA_PERSISTENT_LOSS;
	if (unlikely(state == NVME_ANA_CHANGE))
		return NVME_SC_ANA_TRANSITION;
	return 0;
}