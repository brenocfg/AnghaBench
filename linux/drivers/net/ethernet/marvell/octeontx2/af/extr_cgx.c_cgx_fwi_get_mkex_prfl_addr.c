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
struct cgx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGX_CMD_GET_MKEX_PRFL_ADDR ; 
 int /*<<< orphan*/  CMDREG_ID ; 
 int /*<<< orphan*/  FIELD_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIELD_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RESP_MKEX_PRFL_ADDR ; 
 int cgx_fwi_cmd_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct cgx*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int cgx_fwi_get_mkex_prfl_addr(u64 *prfl_addr,
					     struct cgx *cgx)
{
	u64 req = 0;
	u64 resp;
	int err;

	req = FIELD_SET(CMDREG_ID, CGX_CMD_GET_MKEX_PRFL_ADDR, req);
	err = cgx_fwi_cmd_generic(req, &resp, cgx, 0);
	if (!err)
		*prfl_addr = FIELD_GET(RESP_MKEX_PRFL_ADDR, resp);

	return err;
}