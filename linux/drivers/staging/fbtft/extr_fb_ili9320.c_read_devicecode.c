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
typedef  int u8 ;
struct TYPE_2__ {int (* read ) (struct fbtft_par*,int*,int) ;} ;
struct fbtft_par {TYPE_1__ fbtftops; } ;

/* Variables and functions */
 int stub1 (struct fbtft_par*,int*,int) ; 
 int /*<<< orphan*/  write_reg (struct fbtft_par*,int) ; 

__attribute__((used)) static unsigned int read_devicecode(struct fbtft_par *par)
{
	int ret;
	u8 rxbuf[8] = {0, };

	write_reg(par, 0x0000);
	ret = par->fbtftops.read(par, rxbuf, 4);
	return (rxbuf[2] << 8) | rxbuf[3];
}