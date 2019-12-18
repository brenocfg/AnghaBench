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
struct nvec_msg {int /*<<< orphan*/  used; } ;
struct nvec_chip {int /*<<< orphan*/  dev; struct nvec_msg* msg_pool; } ;
typedef  enum nvec_msg_category { ____Placeholder_nvec_msg_category } nvec_msg_category ;

/* Variables and functions */
 int NVEC_MSG_TX ; 
 int NVEC_POOL_SIZE ; 
 scalar_t__ atomic_xchg (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static struct nvec_msg *nvec_msg_alloc(struct nvec_chip *nvec,
				       enum nvec_msg_category category)
{
	int i = (category == NVEC_MSG_TX) ? (NVEC_POOL_SIZE / 4) : 0;

	for (; i < NVEC_POOL_SIZE; i++) {
		if (atomic_xchg(&nvec->msg_pool[i].used, 1) == 0) {
			dev_vdbg(nvec->dev, "INFO: Allocate %i\n", i);
			return &nvec->msg_pool[i];
		}
	}

	dev_err(nvec->dev, "could not allocate %s buffer\n",
		(category == NVEC_MSG_TX) ? "TX" : "RX");

	return NULL;
}