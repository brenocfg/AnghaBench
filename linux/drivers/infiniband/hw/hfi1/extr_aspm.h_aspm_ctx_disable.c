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
struct hfi1_ctxtdata {int /*<<< orphan*/  aspm_intr_supported; } ;

/* Variables and functions */
 int /*<<< orphan*/  __aspm_ctx_disable (struct hfi1_ctxtdata*) ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static inline void aspm_ctx_disable(struct hfi1_ctxtdata *rcd)
{
	/* Quickest exit for minimum impact */
	if (likely(!rcd->aspm_intr_supported))
		return;

	__aspm_ctx_disable(rcd);
}