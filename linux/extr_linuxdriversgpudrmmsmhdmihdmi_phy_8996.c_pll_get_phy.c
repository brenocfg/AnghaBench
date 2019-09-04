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
struct hdmi_pll_8996 {int /*<<< orphan*/  pdev; } ;
struct hdmi_phy {int dummy; } ;

/* Variables and functions */
 struct hdmi_phy* platform_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct hdmi_phy *pll_get_phy(struct hdmi_pll_8996 *pll)
{
	return platform_get_drvdata(pll->pdev);
}