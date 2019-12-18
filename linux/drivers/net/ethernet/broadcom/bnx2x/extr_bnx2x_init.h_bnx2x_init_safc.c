#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cmng_init_input {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  safc_timeout_usec; } ;
struct TYPE_4__ {TYPE_1__ safc_vars; } ;
struct cmng_init {TYPE_2__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAFC_TIMEOUT_USEC ; 

__attribute__((used)) static inline void bnx2x_init_safc(const struct cmng_init_input *input_data,
				   struct cmng_init *ram_data)
{
	/* in microSeconds */
	ram_data->port.safc_vars.safc_timeout_usec = SAFC_TIMEOUT_USEC;
}