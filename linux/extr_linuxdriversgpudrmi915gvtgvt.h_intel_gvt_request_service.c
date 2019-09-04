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
struct intel_gvt {int /*<<< orphan*/  service_thread_wq; int /*<<< orphan*/  service_request; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_bit (int,void*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void intel_gvt_request_service(struct intel_gvt *gvt,
		int service)
{
	set_bit(service, (void *)&gvt->service_request);
	wake_up(&gvt->service_thread_wq);
}