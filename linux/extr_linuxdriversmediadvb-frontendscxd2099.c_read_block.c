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
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct TYPE_2__ {int max_i2c; } ;
struct cxd {scalar_t__ lastaddress; int /*<<< orphan*/  regmap; TYPE_1__ cfg; } ;

/* Variables and functions */
 int regmap_raw_read (int /*<<< orphan*/ ,int,scalar_t__*,int) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int read_block(struct cxd *ci, u8 adr, u8 *data, u16 n)
{
	int status = 0;

	if (ci->lastaddress != adr)
		status = regmap_write(ci->regmap, 0, adr);
	if (!status) {
		ci->lastaddress = adr;

		while (n) {
			int len = n;

			if (ci->cfg.max_i2c && len > ci->cfg.max_i2c)
				len = ci->cfg.max_i2c;
			status = regmap_raw_read(ci->regmap, 1, data, len);
			if (status)
				return status;
			data += len;
			n -= len;
		}
	}
	return status;
}