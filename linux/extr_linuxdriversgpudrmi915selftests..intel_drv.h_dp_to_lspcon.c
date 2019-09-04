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
struct intel_lspcon {int dummy; } ;
struct intel_dp {int dummy; } ;
struct TYPE_2__ {struct intel_lspcon lspcon; } ;

/* Variables and functions */
 TYPE_1__* dp_to_dig_port (struct intel_dp*) ; 

__attribute__((used)) static inline struct intel_lspcon *
dp_to_lspcon(struct intel_dp *intel_dp)
{
	return &dp_to_dig_port(intel_dp)->lspcon;
}