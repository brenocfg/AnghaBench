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
typedef  int /*<<< orphan*/  u8 ;
struct edt_ft5x06_ts_data {TYPE_1__* client; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err_ratelimited (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool edt_ft5x06_ts_check_crc(struct edt_ft5x06_ts_data *tsdata,
				    u8 *buf, int buflen)
{
	int i;
	u8 crc = 0;

	for (i = 0; i < buflen - 1; i++)
		crc ^= buf[i];

	if (crc != buf[buflen-1]) {
		dev_err_ratelimited(&tsdata->client->dev,
				    "crc error: 0x%02x expected, got 0x%02x\n",
				    crc, buf[buflen-1]);
		return false;
	}

	return true;
}