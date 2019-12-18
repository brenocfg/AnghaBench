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
typedef  int u32 ;
struct exynos_srom {scalar_t__ reg_base; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int*) ; 
 int EINVAL ; 
 scalar_t__ EXYNOS_SROM_BC0 ; 
 int EXYNOS_SROM_BCX__PMC__SHIFT ; 
 int EXYNOS_SROM_BCX__TACC__SHIFT ; 
 int EXYNOS_SROM_BCX__TACP__SHIFT ; 
 int EXYNOS_SROM_BCX__TACS__SHIFT ; 
 int EXYNOS_SROM_BCX__TCAH__SHIFT ; 
 int EXYNOS_SROM_BCX__TCOH__SHIFT ; 
 int EXYNOS_SROM_BCX__TCOS__SHIFT ; 
 scalar_t__ EXYNOS_SROM_BW ; 
 int EXYNOS_SROM_BW__BYTEENABLE__SHIFT ; 
 int EXYNOS_SROM_BW__CS_MASK ; 
 int EXYNOS_SROM_BW__DATAWIDTH__SHIFT ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,int*) ; 
 scalar_t__ of_property_read_u32_array (struct device_node*,char*,int*,int /*<<< orphan*/ ) ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int exynos_srom_configure_bank(struct exynos_srom *srom,
				      struct device_node *np)
{
	u32 bank, width, pmc = 0;
	u32 timing[6];
	u32 cs, bw;

	if (of_property_read_u32(np, "reg", &bank))
		return -EINVAL;
	if (of_property_read_u32(np, "reg-io-width", &width))
		width = 1;
	if (of_property_read_bool(np, "samsung,srom-page-mode"))
		pmc = 1 << EXYNOS_SROM_BCX__PMC__SHIFT;
	if (of_property_read_u32_array(np, "samsung,srom-timing", timing,
				       ARRAY_SIZE(timing)))
		return -EINVAL;

	bank *= 4; /* Convert bank into shift/offset */

	cs = 1 << EXYNOS_SROM_BW__BYTEENABLE__SHIFT;
	if (width == 2)
		cs |= 1 << EXYNOS_SROM_BW__DATAWIDTH__SHIFT;

	bw = readl_relaxed(srom->reg_base + EXYNOS_SROM_BW);
	bw = (bw & ~(EXYNOS_SROM_BW__CS_MASK << bank)) | (cs << bank);
	writel_relaxed(bw, srom->reg_base + EXYNOS_SROM_BW);

	writel_relaxed(pmc | (timing[0] << EXYNOS_SROM_BCX__TACP__SHIFT) |
		       (timing[1] << EXYNOS_SROM_BCX__TCAH__SHIFT) |
		       (timing[2] << EXYNOS_SROM_BCX__TCOH__SHIFT) |
		       (timing[3] << EXYNOS_SROM_BCX__TACC__SHIFT) |
		       (timing[4] << EXYNOS_SROM_BCX__TCOS__SHIFT) |
		       (timing[5] << EXYNOS_SROM_BCX__TACS__SHIFT),
		       srom->reg_base + EXYNOS_SROM_BC0 + bank);

	return 0;
}