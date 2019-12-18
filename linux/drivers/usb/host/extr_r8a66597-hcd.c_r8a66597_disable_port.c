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
typedef  int u16 ;
struct r8a66597 {int dummy; } ;

/* Variables and functions */
 int DCFM ; 
 int DRPD ; 
 int EDGESTS ; 
 int HSE ; 
 int /*<<< orphan*/  SOFCFG ; 
 int /*<<< orphan*/  get_intenb_reg (int) ; 
 int /*<<< orphan*/  get_intsts_reg (int) ; 
 int /*<<< orphan*/  get_syscfg_reg (int) ; 
 int /*<<< orphan*/  r8a66597_bclr (struct r8a66597*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8a66597_port_power (struct r8a66597*,int,int /*<<< orphan*/ ) ; 
 int r8a66597_read (struct r8a66597*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8a66597_write (struct r8a66597*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void r8a66597_disable_port(struct r8a66597 *r8a66597, int port)
{
	u16 val, tmp;

	r8a66597_write(r8a66597, 0, get_intenb_reg(port));
	r8a66597_write(r8a66597, 0, get_intsts_reg(port));

	r8a66597_port_power(r8a66597, port, 0);

	do {
		tmp = r8a66597_read(r8a66597, SOFCFG) & EDGESTS;
		udelay(640);
	} while (tmp == EDGESTS);

	val = port ? DRPD : DCFM | DRPD;
	r8a66597_bclr(r8a66597, val, get_syscfg_reg(port));
	r8a66597_bclr(r8a66597, HSE, get_syscfg_reg(port));
}