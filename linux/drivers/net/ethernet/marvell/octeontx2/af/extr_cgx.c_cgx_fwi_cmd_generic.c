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
typedef  int /*<<< orphan*/  u64 ;
struct lmac {int dummy; } ;
struct cgx {int dummy; } ;

/* Variables and functions */
 scalar_t__ CGX_STAT_FAIL ; 
 int EIO ; 
 int ENODEV ; 
 int /*<<< orphan*/  EVTREG_STAT ; 
 scalar_t__ FIELD_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cgx_fwi_cmd_send (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct lmac*) ; 
 struct lmac* lmac_pdata (int,struct cgx*) ; 

__attribute__((used)) static inline int cgx_fwi_cmd_generic(u64 req, u64 *resp,
				      struct cgx *cgx, int lmac_id)
{
	struct lmac *lmac;
	int err;

	lmac = lmac_pdata(lmac_id, cgx);
	if (!lmac)
		return -ENODEV;

	err = cgx_fwi_cmd_send(req, resp, lmac);

	/* Check for valid response */
	if (!err) {
		if (FIELD_GET(EVTREG_STAT, *resp) == CGX_STAT_FAIL)
			return -EIO;
		else
			return 0;
	}

	return err;
}