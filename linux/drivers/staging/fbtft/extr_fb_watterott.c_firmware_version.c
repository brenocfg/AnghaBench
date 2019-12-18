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
typedef  char u8 ;
struct TYPE_2__ {int /*<<< orphan*/  (* read ) (struct fbtft_par*,char*,int) ;} ;
struct fbtft_par {TYPE_1__ fbtftops; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_VERSION ; 
 int /*<<< orphan*/  stub1 (struct fbtft_par*,char*,int) ; 
 int /*<<< orphan*/  write_reg (struct fbtft_par*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int firmware_version(struct fbtft_par *par)
{
	u8 rxbuf[4] = {0, };

	write_reg(par, CMD_VERSION);
	par->fbtftops.read(par, rxbuf, 4);
	if (rxbuf[1] != '.')
		return 0;

	return (rxbuf[0] - '0') << 8 | (rxbuf[2] - '0') << 4 | (rxbuf[3] - '0');
}