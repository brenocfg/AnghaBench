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
typedef  int u16 ;
struct TYPE_4__ {int /*<<< orphan*/  release_ver; int /*<<< orphan*/  product_code; } ;
struct hideep_ts {int fw_size; int nvm_mask; TYPE_2__ dwz_info; TYPE_1__* client; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HIDEEP_DWZ_INFO ; 
 int /*<<< orphan*/  SW_RESET_IN_PGM (int) ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hideep_enter_pgm (struct hideep_ts*) ; 
 int hideep_pgm_r_mem (struct hideep_ts*,int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int hideep_load_dwz(struct hideep_ts *ts)
{
	u16 product_code;
	int error;

	error = hideep_enter_pgm(ts);
	if (error)
		return error;

	msleep(50);

	error = hideep_pgm_r_mem(ts, HIDEEP_DWZ_INFO,
				 (void *)&ts->dwz_info,
				 sizeof(ts->dwz_info) / sizeof(__be32));

	SW_RESET_IN_PGM(10);
	msleep(50);

	if (error) {
		dev_err(&ts->client->dev,
			"failed to fetch DWZ data: %d\n", error);
		return error;
	}

	product_code = be16_to_cpu(ts->dwz_info.product_code);

	switch (product_code & 0xF0) {
	case 0x40:
		dev_dbg(&ts->client->dev, "used crimson IC");
		ts->fw_size = 1024 * 48;
		ts->nvm_mask = 0x00310000;
		break;
	case 0x60:
		dev_dbg(&ts->client->dev, "used lime IC");
		ts->fw_size = 1024 * 64;
		ts->nvm_mask = 0x0030027B;
		break;
	default:
		dev_err(&ts->client->dev, "product code is wrong: %#04x",
			product_code);
		return -EINVAL;
	}

	dev_dbg(&ts->client->dev, "firmware release version: %#04x",
		be16_to_cpu(ts->dwz_info.release_ver));

	return 0;
}