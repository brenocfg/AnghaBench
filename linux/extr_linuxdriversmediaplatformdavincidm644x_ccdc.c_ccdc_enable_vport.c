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

/* Variables and functions */
 int /*<<< orphan*/  CCDC_DISABLE_VIDEO_PORT ; 
 int /*<<< orphan*/  CCDC_ENABLE_VIDEO_PORT ; 
 int /*<<< orphan*/  CCDC_FMTCFG ; 
 int /*<<< orphan*/  regw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ccdc_enable_vport(int flag)
{
	if (flag)
		/* enable video port */
		regw(CCDC_ENABLE_VIDEO_PORT, CCDC_FMTCFG);
	else
		regw(CCDC_DISABLE_VIDEO_PORT, CCDC_FMTCFG);
}