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
struct intel_lpss {int caps; } ;

/* Variables and functions */
 int LPSS_PRIV_CAPS_NO_IDMA ; 

__attribute__((used)) static bool intel_lpss_has_idma(const struct intel_lpss *lpss)
{
	return (lpss->caps & LPSS_PRIV_CAPS_NO_IDMA) == 0;
}