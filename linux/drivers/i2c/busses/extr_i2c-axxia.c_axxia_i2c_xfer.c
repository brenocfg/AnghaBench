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
struct i2c_msg {int dummy; } ;
struct i2c_adapter {int dummy; } ;
struct axxia_i2c_dev {scalar_t__ msg_err; } ;

/* Variables and functions */
 int /*<<< orphan*/  MST_STATUS_TSS ; 
 int SEQ_LEN ; 
 scalar_t__ axxia_i2c_sequence_ok (struct i2c_msg*,int) ; 
 int axxia_i2c_xfer_msg (struct axxia_i2c_dev*,struct i2c_msg*,int) ; 
 int axxia_i2c_xfer_seq (struct axxia_i2c_dev*,struct i2c_msg*) ; 
 struct axxia_i2c_dev* i2c_get_adapdata (struct i2c_adapter*) ; 
 int /*<<< orphan*/  i2c_int_enable (struct axxia_i2c_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
axxia_i2c_xfer(struct i2c_adapter *adap, struct i2c_msg msgs[], int num)
{
	struct axxia_i2c_dev *idev = i2c_get_adapdata(adap);
	int i;
	int ret = 0;

	idev->msg_err = 0;

	if (axxia_i2c_sequence_ok(msgs, num)) {
		ret = axxia_i2c_xfer_seq(idev, msgs);
		return ret ? : SEQ_LEN;
	}

	i2c_int_enable(idev, MST_STATUS_TSS);

	for (i = 0; ret == 0 && i < num; ++i)
		ret = axxia_i2c_xfer_msg(idev, &msgs[i], i == (num - 1));

	return ret ? : i;
}