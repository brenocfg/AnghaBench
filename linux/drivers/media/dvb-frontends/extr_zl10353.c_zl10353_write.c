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
struct dvb_frontend {int dummy; } ;

/* Variables and functions */
 int zl10353_single_write (struct dvb_frontend*,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 

__attribute__((used)) static int zl10353_write(struct dvb_frontend *fe, const u8 ibuf[], int ilen)
{
	int err, i;
	for (i = 0; i < ilen - 1; i++)
		if ((err = zl10353_single_write(fe, ibuf[0] + i, ibuf[i + 1])))
			return err;

	return 0;
}