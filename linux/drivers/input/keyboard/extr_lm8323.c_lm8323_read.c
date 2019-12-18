#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct lm8323_chip {TYPE_1__* client; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,...) ; 
 int i2c_master_recv (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int i2c_master_send (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int lm8323_read(struct lm8323_chip *lm, u8 cmd, u8 *buf, int len)
{
	int ret;

	/*
	 * If the host is asleep while we send the byte, we can get a NACK
	 * back while it wakes up, so try again, once.
	 */
	ret = i2c_master_send(lm->client, &cmd, 1);
	if (unlikely(ret == -EREMOTEIO))
		ret = i2c_master_send(lm->client, &cmd, 1);
	if (unlikely(ret != 1)) {
		dev_err(&lm->client->dev, "sending read cmd 0x%02x failed\n",
			cmd);
		return 0;
	}

	ret = i2c_master_recv(lm->client, buf, len);
	if (unlikely(ret != len))
		dev_err(&lm->client->dev, "wanted %d bytes, got %d\n",
			len, ret);

	return ret;
}