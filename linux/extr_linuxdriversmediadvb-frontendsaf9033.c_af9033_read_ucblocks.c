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
typedef  int /*<<< orphan*/  u32 ;
struct dvb_frontend {struct af9033_dev* demodulator_priv; } ;
struct af9033_dev {int /*<<< orphan*/  error_block_count; } ;

/* Variables and functions */

__attribute__((used)) static int af9033_read_ucblocks(struct dvb_frontend *fe, u32 *ucblocks)
{
	struct af9033_dev *dev = fe->demodulator_priv;

	*ucblocks = dev->error_block_count;

	return 0;
}