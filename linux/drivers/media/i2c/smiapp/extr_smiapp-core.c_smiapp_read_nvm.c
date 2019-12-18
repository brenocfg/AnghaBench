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
typedef  int u32 ;
struct smiapp_sensor {int nvm_size; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int SMIAPP_DATA_TRANSFER_IF_1_CTRL_EN ; 
 int SMIAPP_DATA_TRANSFER_IF_1_CTRL_RD_EN ; 
 int SMIAPP_DATA_TRANSFER_IF_1_STATUS_RD_READY ; 
 int SMIAPP_NVM_PAGE_SIZE ; 
 int /*<<< orphan*/  SMIAPP_REG_U8_DATA_TRANSFER_IF_1_CTRL ; 
 scalar_t__ SMIAPP_REG_U8_DATA_TRANSFER_IF_1_DATA_0 ; 
 int /*<<< orphan*/  SMIAPP_REG_U8_DATA_TRANSFER_IF_1_PAGE_SELECT ; 
 scalar_t__ SMIAPP_REG_U8_DATA_TRANSFER_IF_1_STATUS ; 
 int smiapp_read (struct smiapp_sensor*,scalar_t__,int*) ; 
 int smiapp_write (struct smiapp_sensor*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int smiapp_read_nvm(struct smiapp_sensor *sensor,
			   unsigned char *nvm)
{
	u32 i, s, p, np, v;
	int rval = 0, rval2;

	np = sensor->nvm_size / SMIAPP_NVM_PAGE_SIZE;
	for (p = 0; p < np; p++) {
		rval = smiapp_write(
			sensor,
			SMIAPP_REG_U8_DATA_TRANSFER_IF_1_PAGE_SELECT, p);
		if (rval)
			goto out;

		rval = smiapp_write(sensor,
				    SMIAPP_REG_U8_DATA_TRANSFER_IF_1_CTRL,
				    SMIAPP_DATA_TRANSFER_IF_1_CTRL_EN |
				    SMIAPP_DATA_TRANSFER_IF_1_CTRL_RD_EN);
		if (rval)
			goto out;

		for (i = 1000; i > 0; i--) {
			rval = smiapp_read(
				sensor,
				SMIAPP_REG_U8_DATA_TRANSFER_IF_1_STATUS, &s);

			if (rval)
				goto out;

			if (s & SMIAPP_DATA_TRANSFER_IF_1_STATUS_RD_READY)
				break;

		}
		if (!i) {
			rval = -ETIMEDOUT;
			goto out;
		}

		for (i = 0; i < SMIAPP_NVM_PAGE_SIZE; i++) {
			rval = smiapp_read(
				sensor,
				SMIAPP_REG_U8_DATA_TRANSFER_IF_1_DATA_0 + i,
				&v);
			if (rval)
				goto out;

			*nvm++ = v;
		}
	}

out:
	rval2 = smiapp_write(sensor, SMIAPP_REG_U8_DATA_TRANSFER_IF_1_CTRL, 0);
	if (rval < 0)
		return rval;
	else
		return rval2;
}