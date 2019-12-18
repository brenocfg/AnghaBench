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
struct sdw_cdns_pdi {int num; int assigned; } ;
struct sdw_cdns {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct sdw_cdns_pdi* devm_kcalloc (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cdns_allocate_pdi(struct sdw_cdns *cdns,
			     struct sdw_cdns_pdi **stream,
			     u32 num, u32 pdi_offset)
{
	struct sdw_cdns_pdi *pdi;
	int i;

	if (!num)
		return 0;

	pdi = devm_kcalloc(cdns->dev, num, sizeof(*pdi), GFP_KERNEL);
	if (!pdi)
		return -ENOMEM;

	for (i = 0; i < num; i++) {
		pdi[i].num = i + pdi_offset;
		pdi[i].assigned = false;
	}

	*stream = pdi;
	return 0;
}