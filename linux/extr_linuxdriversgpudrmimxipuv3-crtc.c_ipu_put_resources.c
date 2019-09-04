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
struct ipu_crtc {int /*<<< orphan*/  di; int /*<<< orphan*/  dc; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_dc_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_di_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ipu_put_resources(struct ipu_crtc *ipu_crtc)
{
	if (!IS_ERR_OR_NULL(ipu_crtc->dc))
		ipu_dc_put(ipu_crtc->dc);
	if (!IS_ERR_OR_NULL(ipu_crtc->di))
		ipu_di_put(ipu_crtc->di);
}