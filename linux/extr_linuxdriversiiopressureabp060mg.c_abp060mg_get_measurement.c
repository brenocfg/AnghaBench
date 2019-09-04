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
typedef  int u16 ;
struct i2c_client {int dummy; } ;
struct abp_state {int /*<<< orphan*/  mreq_len; struct i2c_client* client; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  scalar_t__ __be16 ;

/* Variables and functions */
 int ABP060MG_ERROR_MASK ; 
 int ABP060MG_MAX_COUNTS ; 
 int ABP060MG_MIN_COUNTS ; 
 int /*<<< orphan*/  ABP060MG_RESP_TIME_MS ; 
 int EIO ; 
 int IIO_VAL_INT ; 
 int be16_to_cpu (scalar_t__) ; 
 int i2c_master_recv (struct i2c_client*,int /*<<< orphan*/ *,int) ; 
 int i2c_master_send (struct i2c_client*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep_interruptible (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int abp060mg_get_measurement(struct abp_state *state, int *val)
{
	struct i2c_client *client = state->client;
	__be16 buf[2];
	u16 pressure;
	int ret;

	buf[0] = 0;
	ret = i2c_master_send(client, (u8 *)&buf, state->mreq_len);
	if (ret < 0)
		return ret;

	msleep_interruptible(ABP060MG_RESP_TIME_MS);

	ret = i2c_master_recv(client, (u8 *)&buf, sizeof(buf));
	if (ret < 0)
		return ret;

	pressure = be16_to_cpu(buf[0]);
	if (pressure & ABP060MG_ERROR_MASK)
		return -EIO;

	if (pressure < ABP060MG_MIN_COUNTS || pressure > ABP060MG_MAX_COUNTS)
		return -EIO;

	*val = pressure;

	return IIO_VAL_INT;
}