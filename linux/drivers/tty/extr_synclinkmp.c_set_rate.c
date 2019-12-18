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
typedef  int u32 ;
typedef  int /*<<< orphan*/  SLMP_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  RXS ; 
 int /*<<< orphan*/  TMC ; 
 int /*<<< orphan*/  TXS ; 
 int read_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static void set_rate( SLMP_INFO *info, u32 data_rate )
{
       	u32 TMCValue;
       	unsigned char BRValue;
	u32 Divisor=0;

	/* fBRG = fCLK/(TMC * 2^BR)
	 */
	if (data_rate != 0) {
		Divisor = 14745600/data_rate;
		if (!Divisor)
			Divisor = 1;

		TMCValue = Divisor;

		BRValue = 0;
		if (TMCValue != 1 && TMCValue != 2) {
			/* BRValue of 0 provides 50/50 duty cycle *only* when
			 * TMCValue is 1 or 2. BRValue of 1 to 9 always provides
			 * 50/50 duty cycle.
			 */
			BRValue = 1;
			TMCValue >>= 1;
		}

		/* while TMCValue is too big for TMC register, divide
		 * by 2 and increment BR exponent.
		 */
		for(; TMCValue > 256 && BRValue < 10; BRValue++)
			TMCValue >>= 1;

		write_reg(info, TXS,
			(unsigned char)((read_reg(info, TXS) & 0xf0) | BRValue));
		write_reg(info, RXS,
			(unsigned char)((read_reg(info, RXS) & 0xf0) | BRValue));
		write_reg(info, TMC, (unsigned char)TMCValue);
	}
	else {
		write_reg(info, TXS,0);
		write_reg(info, RXS,0);
		write_reg(info, TMC, 0);
	}
}