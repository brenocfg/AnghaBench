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
struct csiphy_device {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ CSIPHY_3PH_CMN_CSI_COMMON_CTRLn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void csiphy_reset(struct csiphy_device *csiphy)
{
	writel_relaxed(0x1, csiphy->base + CSIPHY_3PH_CMN_CSI_COMMON_CTRLn(0));
	usleep_range(5000, 8000);
	writel_relaxed(0x0, csiphy->base + CSIPHY_3PH_CMN_CSI_COMMON_CTRLn(0));
}