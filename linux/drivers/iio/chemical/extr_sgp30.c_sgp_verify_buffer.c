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
union sgp_reading {int /*<<< orphan*/  start; } ;
typedef  int /*<<< orphan*/  u8 ;
struct sgp_data {TYPE_1__* client; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  SGP_CRC8_INIT ; 
 size_t SGP_CRC8_LEN ; 
 size_t SGP_WORD_LEN ; 
 int /*<<< orphan*/  crc8 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sgp_crc8_table ; 

__attribute__((used)) static int sgp_verify_buffer(const struct sgp_data *data,
			     union sgp_reading *buf, size_t word_count)
{
	size_t size = word_count * (SGP_WORD_LEN + SGP_CRC8_LEN);
	int i;
	u8 crc;
	u8 *data_buf = &buf->start;

	for (i = 0; i < size; i += SGP_WORD_LEN + SGP_CRC8_LEN) {
		crc = crc8(sgp_crc8_table, &data_buf[i], SGP_WORD_LEN,
			   SGP_CRC8_INIT);
		if (crc != data_buf[i + SGP_WORD_LEN]) {
			dev_err(&data->client->dev, "CRC error\n");
			return -EIO;
		}
	}

	return 0;
}