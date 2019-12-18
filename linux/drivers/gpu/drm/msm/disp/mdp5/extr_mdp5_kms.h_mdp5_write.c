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
struct mdp5_kms {scalar_t__ enable_count; scalar_t__ mmio; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  msm_writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline void mdp5_write(struct mdp5_kms *mdp5_kms, u32 reg, u32 data)
{
	WARN_ON(mdp5_kms->enable_count <= 0);
	msm_writel(data, mdp5_kms->mmio + reg);
}