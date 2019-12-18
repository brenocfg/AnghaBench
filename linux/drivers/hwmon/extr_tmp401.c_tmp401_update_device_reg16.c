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
typedef  int /*<<< orphan*/  u8 ;
struct tmp401_data {scalar_t__ kind; int** temp; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ ** TMP401_TEMP_MSB_READ ; 
 int /*<<< orphan*/ ** TMP432_TEMP_MSB_READ ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_read_word_swapped (struct i2c_client*,int /*<<< orphan*/ ) ; 
 scalar_t__ tmp411 ; 
 scalar_t__ tmp432 ; 

__attribute__((used)) static int tmp401_update_device_reg16(struct i2c_client *client,
				      struct tmp401_data *data)
{
	int i, j, val;
	int num_regs = data->kind == tmp411 ? 6 : 4;
	int num_sensors = data->kind == tmp432 ? 3 : 2;

	for (i = 0; i < num_sensors; i++) {		/* local / r1 / r2 */
		for (j = 0; j < num_regs; j++) {	/* temp / low / ... */
			u8 regaddr;

			regaddr = data->kind == tmp432 ?
						TMP432_TEMP_MSB_READ[j][i] :
						TMP401_TEMP_MSB_READ[j][i];
			if (j == 3) { /* crit is msb only */
				val = i2c_smbus_read_byte_data(client, regaddr);
			} else {
				val = i2c_smbus_read_word_swapped(client,
								  regaddr);
			}
			if (val < 0)
				return val;

			data->temp[j][i] = j == 3 ? val << 8 : val;
		}
	}
	return 0;
}