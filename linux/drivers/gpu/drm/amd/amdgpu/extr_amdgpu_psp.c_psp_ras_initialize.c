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
struct TYPE_2__ {int /*<<< orphan*/  ras_initialized; } ;
struct psp_context {TYPE_1__ ras; } ;

/* Variables and functions */
 int psp_ras_init_shared_buf (struct psp_context*) ; 
 int psp_ras_load (struct psp_context*) ; 

__attribute__((used)) static int psp_ras_initialize(struct psp_context *psp)
{
	int ret;

	if (!psp->ras.ras_initialized) {
		ret = psp_ras_init_shared_buf(psp);
		if (ret)
			return ret;
	}

	ret = psp_ras_load(psp);
	if (ret)
		return ret;

	return 0;
}