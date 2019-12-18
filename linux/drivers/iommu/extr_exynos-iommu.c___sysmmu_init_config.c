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
struct sysmmu_drvdata {scalar_t__ version; scalar_t__ sfrbase; } ;

/* Variables and functions */
 unsigned int CFG_ACGEN ; 
 unsigned int CFG_EAP ; 
 unsigned int CFG_FLPDCACHE ; 
 unsigned int CFG_LRU ; 
 unsigned int CFG_QOS (int) ; 
 unsigned int CFG_SYSSEL ; 
 scalar_t__ MAKE_MMU_VER (int,int) ; 
 scalar_t__ REG_MMU_CFG ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static void __sysmmu_init_config(struct sysmmu_drvdata *data)
{
	unsigned int cfg;

	if (data->version <= MAKE_MMU_VER(3, 1))
		cfg = CFG_LRU | CFG_QOS(15);
	else if (data->version <= MAKE_MMU_VER(3, 2))
		cfg = CFG_LRU | CFG_QOS(15) | CFG_FLPDCACHE | CFG_SYSSEL;
	else
		cfg = CFG_QOS(15) | CFG_FLPDCACHE | CFG_ACGEN;

	cfg |= CFG_EAP; /* enable access protection bits check */

	writel(cfg, data->sfrbase + REG_MMU_CFG);
}