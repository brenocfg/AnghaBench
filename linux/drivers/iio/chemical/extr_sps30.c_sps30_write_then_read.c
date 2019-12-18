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
struct sps30_state {int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int EIO ; 
 int i2c_master_recv (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int i2c_master_send (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int sps30_write_then_read(struct sps30_state *state, u8 *txbuf,
				 int txsize, u8 *rxbuf, int rxsize)
{
	int ret;

	/*
	 * Sensor does not support repeated start so instead of
	 * sending two i2c messages in a row we just send one by one.
	 */
	ret = i2c_master_send(state->client, txbuf, txsize);
	if (ret != txsize)
		return ret < 0 ? ret : -EIO;

	if (!rxbuf)
		return 0;

	ret = i2c_master_recv(state->client, rxbuf, rxsize);
	if (ret != rxsize)
		return ret < 0 ? ret : -EIO;

	return 0;
}