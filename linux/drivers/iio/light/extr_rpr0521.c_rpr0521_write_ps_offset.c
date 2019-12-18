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
struct rpr0521_data {TYPE_1__* client; int /*<<< orphan*/  regmap; } ;
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  RPR0521_REG_PS_OFFSET_LSB ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int regmap_raw_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int rpr0521_write_ps_offset(struct rpr0521_data *data, int offset)
{
	int ret;
	__le16 buffer;

	buffer = cpu_to_le16(offset & 0x3ff);
	ret = regmap_raw_write(data->regmap,
		RPR0521_REG_PS_OFFSET_LSB, &buffer, sizeof(buffer));

	if (ret < 0) {
		dev_err(&data->client->dev, "Failed to write PS OFFSET register\n");
		return ret;
	}

	return ret;
}