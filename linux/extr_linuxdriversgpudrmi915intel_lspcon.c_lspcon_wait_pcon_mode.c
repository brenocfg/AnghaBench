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
struct intel_lspcon {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_LSPCON_MODE_PCON ; 
 int /*<<< orphan*/  lspcon_wait_mode (struct intel_lspcon*,int /*<<< orphan*/ ) ; 

void lspcon_wait_pcon_mode(struct intel_lspcon *lspcon)
{
	lspcon_wait_mode(lspcon, DRM_LSPCON_MODE_PCON);
}