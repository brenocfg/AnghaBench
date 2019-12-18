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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct i2c_device {TYPE_1__ adapter; } ;

/* Variables and functions */
 int MAX_RETRIES ; 
 int /*<<< orphan*/  SMBHSTSTS (struct i2c_device*) ; 
 int SMBHSTSTS_INTR ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int inb_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb_p (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void i801_wait_hwpec(struct i2c_device *priv)
{
	int timeout = 0;
	int status;

	do {
		usleep_range(250, 500);
		status = inb_p(SMBHSTSTS(priv));
	} while ((!(status & SMBHSTSTS_INTR)) && (timeout++ < MAX_RETRIES));

	if (timeout > MAX_RETRIES)
		dev_dbg(&priv->adapter.dev, "PEC Timeout!\n");

	outb_p(status, SMBHSTSTS(priv));
}