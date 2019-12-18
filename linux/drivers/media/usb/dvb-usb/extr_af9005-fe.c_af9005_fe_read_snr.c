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
typedef  int /*<<< orphan*/  u16 ;
struct dvb_frontend {int dummy; } ;

/* Variables and functions */
 int ENOSYS ; 

__attribute__((used)) static int af9005_fe_read_snr(struct dvb_frontend *fe, u16 * snr)
{
	/* the snr can be derived from the ber and the modulation
	   but I don't think this kind of complex calculations belong
	   in the driver. I may be wrong.... */
	return -ENOSYS;
}