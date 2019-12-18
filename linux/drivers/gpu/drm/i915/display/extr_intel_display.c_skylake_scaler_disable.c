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
struct intel_crtc {int num_scalers; } ;

/* Variables and functions */
 int /*<<< orphan*/  skl_detach_scaler (struct intel_crtc*,int) ; 

__attribute__((used)) static void skylake_scaler_disable(struct intel_crtc *crtc)
{
	int i;

	for (i = 0; i < crtc->num_scalers; i++)
		skl_detach_scaler(crtc, i);
}