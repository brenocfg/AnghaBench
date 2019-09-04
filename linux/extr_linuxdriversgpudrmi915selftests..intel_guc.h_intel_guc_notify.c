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
struct intel_guc {int /*<<< orphan*/  (* notify ) (struct intel_guc*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct intel_guc*) ; 

__attribute__((used)) static inline void intel_guc_notify(struct intel_guc *guc)
{
	guc->notify(guc);
}