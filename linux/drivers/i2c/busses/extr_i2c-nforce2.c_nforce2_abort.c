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
struct nforce2_smbus {int dummy; } ;
struct i2c_adapter {int /*<<< orphan*/  dev; struct nforce2_smbus* algo_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_TIMEOUT ; 
 int /*<<< orphan*/  NVIDIA_SMB_CTRL ; 
 unsigned char NVIDIA_SMB_CTRL_ABORT ; 
 int /*<<< orphan*/  NVIDIA_SMB_STATUS_ABRT ; 
 unsigned char NVIDIA_SMB_STATUS_ABRT_STS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 unsigned char inb_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  outb_p (unsigned char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nforce2_abort(struct i2c_adapter *adap)
{
	struct nforce2_smbus *smbus = adap->algo_data;
	int timeout = 0;
	unsigned char temp;

	dev_dbg(&adap->dev, "Aborting current transaction\n");

	outb_p(NVIDIA_SMB_CTRL_ABORT, NVIDIA_SMB_CTRL);
	do {
		msleep(1);
		temp = inb_p(NVIDIA_SMB_STATUS_ABRT);
	} while (!(temp & NVIDIA_SMB_STATUS_ABRT_STS) &&
			(timeout++ < MAX_TIMEOUT));
	if (!(temp & NVIDIA_SMB_STATUS_ABRT_STS))
		dev_err(&adap->dev, "Can't reset the smbus\n");
	outb_p(NVIDIA_SMB_STATUS_ABRT_STS, NVIDIA_SMB_STATUS_ABRT);
}