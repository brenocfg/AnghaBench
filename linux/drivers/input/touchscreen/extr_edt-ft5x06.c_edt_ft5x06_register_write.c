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
typedef  int u8 ;
struct edt_ft5x06_ts_data {int version; int /*<<< orphan*/  client; int /*<<< orphan*/  factory_mode; } ;

/* Variables and functions */
#define  EDT_M06 132 
#define  EDT_M09 131 
#define  EDT_M12 130 
 int EINVAL ; 
#define  EV_FT 129 
#define  GENERIC_FT 128 
 int edt_ft5x06_ts_readwrite (int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int edt_ft5x06_register_write(struct edt_ft5x06_ts_data *tsdata,
				     u8 addr, u8 value)
{
	u8 wrbuf[4];

	switch (tsdata->version) {
	case EDT_M06:
		wrbuf[0] = tsdata->factory_mode ? 0xf3 : 0xfc;
		wrbuf[1] = tsdata->factory_mode ? addr & 0x7f : addr & 0x3f;
		wrbuf[2] = value;
		wrbuf[3] = wrbuf[0] ^ wrbuf[1] ^ wrbuf[2];
		return edt_ft5x06_ts_readwrite(tsdata->client, 4,
					wrbuf, 0, NULL);
	/* fallthrough */
	case EDT_M09:
	case EDT_M12:
	case EV_FT:
	case GENERIC_FT:
		wrbuf[0] = addr;
		wrbuf[1] = value;

		return edt_ft5x06_ts_readwrite(tsdata->client, 2,
					wrbuf, 0, NULL);

	default:
		return -EINVAL;
	}
}