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
struct qtnf_shm_ipc {int /*<<< orphan*/  (* irq_handler ) (struct qtnf_shm_ipc*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct qtnf_shm_ipc*) ; 

__attribute__((used)) static inline void qtnf_shm_ipc_irq_handler(struct qtnf_shm_ipc *ipc)
{
	ipc->irq_handler(ipc);
}