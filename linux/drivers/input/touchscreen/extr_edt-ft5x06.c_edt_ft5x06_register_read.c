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
typedef  int u8 ;
struct edt_ft5x06_ts_data {int version; TYPE_1__* client; int /*<<< orphan*/  factory_mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  EDT_M06 132 
#define  EDT_M09 131 
#define  EDT_M12 130 
 int EINVAL ; 
 int EIO ; 
#define  EV_FT 129 
#define  GENERIC_FT 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int) ; 
 int edt_ft5x06_ts_readwrite (TYPE_1__*,int,int*,int,int*) ; 

__attribute__((used)) static int edt_ft5x06_register_read(struct edt_ft5x06_ts_data *tsdata,
				    u8 addr)
{
	u8 wrbuf[2], rdbuf[2];
	int error;

	switch (tsdata->version) {
	case EDT_M06:
		wrbuf[0] = tsdata->factory_mode ? 0xf3 : 0xfc;
		wrbuf[1] = tsdata->factory_mode ? addr & 0x7f : addr & 0x3f;
		wrbuf[1] |= tsdata->factory_mode ? 0x80 : 0x40;

		error = edt_ft5x06_ts_readwrite(tsdata->client, 2, wrbuf, 2,
						rdbuf);
		if (error)
			return error;

		if ((wrbuf[0] ^ wrbuf[1] ^ rdbuf[0]) != rdbuf[1]) {
			dev_err(&tsdata->client->dev,
				"crc error: 0x%02x expected, got 0x%02x\n",
				wrbuf[0] ^ wrbuf[1] ^ rdbuf[0],
				rdbuf[1]);
			return -EIO;
		}
		break;

	/* fallthrough */
	case EDT_M09:
	case EDT_M12:
	case EV_FT:
	case GENERIC_FT:
		wrbuf[0] = addr;
		error = edt_ft5x06_ts_readwrite(tsdata->client, 1,
						wrbuf, 1, rdbuf);
		if (error)
			return error;
		break;

	default:
		return -EINVAL;
	}

	return rdbuf[0];
}