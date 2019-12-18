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
typedef  scalar_t__ u32 ;
struct mdp5_mdss {scalar_t__ mmio; } ;

/* Variables and functions */
 scalar_t__ msm_readl (scalar_t__) ; 

__attribute__((used)) static inline u32 mdss_read(struct mdp5_mdss *mdp5_mdss, u32 reg)
{
	return msm_readl(mdp5_mdss->mmio + reg);
}