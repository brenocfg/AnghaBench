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
struct iss_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  omap4iss_csi2_cleanup (struct iss_device*) ; 
 int /*<<< orphan*/  omap4iss_ipipe_cleanup (struct iss_device*) ; 
 int /*<<< orphan*/  omap4iss_ipipeif_cleanup (struct iss_device*) ; 
 int /*<<< orphan*/  omap4iss_resizer_cleanup (struct iss_device*) ; 

__attribute__((used)) static void iss_cleanup_modules(struct iss_device *iss)
{
	omap4iss_csi2_cleanup(iss);
	omap4iss_ipipeif_cleanup(iss);
	omap4iss_ipipe_cleanup(iss);
	omap4iss_resizer_cleanup(iss);
}