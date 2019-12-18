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
struct brcmu_d11inf {scalar_t__ io_type; int /*<<< orphan*/  decchspec; int /*<<< orphan*/  encchspec; } ;

/* Variables and functions */
 scalar_t__ BRCMU_D11N_IOTYPE ; 
 int /*<<< orphan*/  brcmu_d11ac_decchspec ; 
 int /*<<< orphan*/  brcmu_d11ac_encchspec ; 
 int /*<<< orphan*/  brcmu_d11n_decchspec ; 
 int /*<<< orphan*/  brcmu_d11n_encchspec ; 

void brcmu_d11_attach(struct brcmu_d11inf *d11inf)
{
	if (d11inf->io_type == BRCMU_D11N_IOTYPE) {
		d11inf->encchspec = brcmu_d11n_encchspec;
		d11inf->decchspec = brcmu_d11n_decchspec;
	} else {
		d11inf->encchspec = brcmu_d11ac_encchspec;
		d11inf->decchspec = brcmu_d11ac_decchspec;
	}
}