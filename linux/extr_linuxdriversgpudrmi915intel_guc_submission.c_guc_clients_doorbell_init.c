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
struct intel_guc {scalar_t__ execbuf_client; scalar_t__ preempt_client; } ;

/* Variables and functions */
 int create_doorbell (scalar_t__) ; 
 int /*<<< orphan*/  destroy_doorbell (scalar_t__) ; 

__attribute__((used)) static int guc_clients_doorbell_init(struct intel_guc *guc)
{
	int ret;

	ret = create_doorbell(guc->execbuf_client);
	if (ret)
		return ret;

	if (guc->preempt_client) {
		ret = create_doorbell(guc->preempt_client);
		if (ret) {
			destroy_doorbell(guc->execbuf_client);
			return ret;
		}
	}

	return 0;
}