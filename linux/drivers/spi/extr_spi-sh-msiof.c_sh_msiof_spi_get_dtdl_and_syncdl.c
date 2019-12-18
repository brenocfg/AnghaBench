#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct sh_msiof_spi_priv {TYPE_2__* info; TYPE_1__* pdev; } ;
struct TYPE_4__ {int dtdl; int syncdl; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int MDR1_DTDL_SHIFT ; 
 int MDR1_SYNCDL_SHIFT ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int sh_msiof_get_delay_bit (int) ; 

__attribute__((used)) static u32 sh_msiof_spi_get_dtdl_and_syncdl(struct sh_msiof_spi_priv *p)
{
	u32 val;

	if (!p->info)
		return 0;

	/* check if DTDL and SYNCDL is allowed value */
	if (p->info->dtdl > 200 || p->info->syncdl > 300) {
		dev_warn(&p->pdev->dev, "DTDL or SYNCDL is too large\n");
		return 0;
	}

	/* check if the sum of DTDL and SYNCDL becomes an integer value  */
	if ((p->info->dtdl + p->info->syncdl) % 100) {
		dev_warn(&p->pdev->dev, "the sum of DTDL/SYNCDL is not good\n");
		return 0;
	}

	val = sh_msiof_get_delay_bit(p->info->dtdl) << MDR1_DTDL_SHIFT;
	val |= sh_msiof_get_delay_bit(p->info->syncdl) << MDR1_SYNCDL_SHIFT;

	return val;
}