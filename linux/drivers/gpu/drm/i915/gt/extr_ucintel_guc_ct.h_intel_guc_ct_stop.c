#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int enabled; } ;
struct intel_guc_ct {TYPE_1__ host_channel; } ;

/* Variables and functions */

__attribute__((used)) static inline void intel_guc_ct_stop(struct intel_guc_ct *ct)
{
	ct->host_channel.enabled = false;
}