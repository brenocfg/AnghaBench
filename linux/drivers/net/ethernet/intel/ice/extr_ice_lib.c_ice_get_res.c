#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct ice_res_tracker {scalar_t__ num_entries; } ;
struct ice_pf {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ ICE_RES_VALID_BIT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__,scalar_t__,scalar_t__) ; 
 int ice_search_res (struct ice_res_tracker*,scalar_t__,scalar_t__) ; 

int
ice_get_res(struct ice_pf *pf, struct ice_res_tracker *res, u16 needed, u16 id)
{
	if (!res || !pf)
		return -EINVAL;

	if (!needed || needed > res->num_entries || id >= ICE_RES_VALID_BIT) {
		dev_err(&pf->pdev->dev,
			"param err: needed=%d, num_entries = %d id=0x%04x\n",
			needed, res->num_entries, id);
		return -EINVAL;
	}

	return ice_search_res(res, needed, id);
}