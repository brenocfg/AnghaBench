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
struct meson_ao_cec_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEC_RX_CLEAR_BUF ; 
 int /*<<< orphan*/  CEC_RX_MSG_CMD ; 
 int /*<<< orphan*/  CEC_TX_CLEAR_BUF ; 
 int /*<<< orphan*/  CEC_TX_MSG_CMD ; 
 int RX_DISABLE ; 
 int RX_NO_OP ; 
 int TX_ABORT ; 
 int TX_NO_OP ; 
 int /*<<< orphan*/  meson_ao_cec_write (struct meson_ao_cec_device*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static inline int meson_ao_cec_clear(struct meson_ao_cec_device *ao_cec)
{
	int ret = 0;

	meson_ao_cec_write(ao_cec, CEC_RX_MSG_CMD, RX_DISABLE, &ret);
	meson_ao_cec_write(ao_cec, CEC_TX_MSG_CMD, TX_ABORT, &ret);
	meson_ao_cec_write(ao_cec, CEC_RX_CLEAR_BUF, 1, &ret);
	meson_ao_cec_write(ao_cec, CEC_TX_CLEAR_BUF, 1, &ret);
	if (ret)
		return ret;

	udelay(100);

	meson_ao_cec_write(ao_cec, CEC_RX_CLEAR_BUF, 0, &ret);
	meson_ao_cec_write(ao_cec, CEC_TX_CLEAR_BUF, 0, &ret);
	if (ret)
		return ret;

	udelay(100);

	meson_ao_cec_write(ao_cec, CEC_RX_MSG_CMD, RX_NO_OP, &ret);
	meson_ao_cec_write(ao_cec, CEC_TX_MSG_CMD, TX_NO_OP, &ret);

	return ret;
}