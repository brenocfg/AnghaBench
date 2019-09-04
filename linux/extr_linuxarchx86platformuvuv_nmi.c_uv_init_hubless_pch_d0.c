#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  data; int /*<<< orphan*/  mask; int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  PAD_OWN_GPP_D_0 ; 
 int* PCH_PCR_GPIO_ADDRESS (int /*<<< orphan*/ ) ; 
 TYPE_1__* init_nmi ; 
 int /*<<< orphan*/  nmi_debug (char*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  uv_init_hubless_pch_io (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void uv_init_hubless_pch_d0(void)
{
	int i, read;

	read = *PCH_PCR_GPIO_ADDRESS(PAD_OWN_GPP_D_0);
	if (read != 0) {
		pr_info("UV: Hubless NMI already configured\n");
		return;
	}

	nmi_debug("UV: Initializing UV Hubless NMI on PCH\n");
	for (i = 0; i < ARRAY_SIZE(init_nmi); i++) {
		uv_init_hubless_pch_io(init_nmi[i].offset,
					init_nmi[i].mask,
					init_nmi[i].data);
	}
}