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
struct hip04_priv {scalar_t__ sysctrl_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  RESET_DREQ_ALL ; 
 scalar_t__ SC_PPE_RESET_DREQ ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void hip04_reset_dreq(struct hip04_priv *priv)
{
#if defined(CONFIG_HI13X1_GMAC)
	writel_relaxed(RESET_DREQ_ALL, priv->sysctrl_base + SC_PPE_RESET_DREQ);
#endif
}