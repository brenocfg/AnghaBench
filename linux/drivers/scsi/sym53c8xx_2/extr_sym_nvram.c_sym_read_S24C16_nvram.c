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
typedef  int u_char ;
struct sym_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLR_BIT ; 
 int /*<<< orphan*/  CLR_CLK ; 
 int INB (struct sym_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OUTB (struct sym_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  S24C16_read_byte (struct sym_device*,int*,int,int*,int*) ; 
 int /*<<< orphan*/  S24C16_set_bit (struct sym_device*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S24C16_start (struct sym_device*,int*) ; 
 int /*<<< orphan*/  S24C16_stop (struct sym_device*,int*) ; 
 int /*<<< orphan*/  S24C16_write_byte (struct sym_device*,int*,int,int*,int*) ; 
 int /*<<< orphan*/  nc_gpcntl ; 
 int /*<<< orphan*/  nc_gpreg ; 

__attribute__((used)) static int sym_read_S24C16_nvram(struct sym_device *np, int offset, u_char *data, int len)
{
	u_char	gpcntl, gpreg;
	u_char	old_gpcntl, old_gpreg;
	u_char	ack_data;
	int	retv = 1;
	int	x;

	/* save current state of GPCNTL and GPREG */
	old_gpreg	= INB(np, nc_gpreg);
	old_gpcntl	= INB(np, nc_gpcntl);
	gpcntl		= old_gpcntl & 0x1c;

	/* set up GPREG & GPCNTL to set GPIO0 and GPIO1 in to known state */
	OUTB(np, nc_gpreg,  old_gpreg);
	OUTB(np, nc_gpcntl, gpcntl);

	/* this is to set NVRAM into a known state with GPIO0/1 both low */
	gpreg = old_gpreg;
	S24C16_set_bit(np, 0, &gpreg, CLR_CLK);
	S24C16_set_bit(np, 0, &gpreg, CLR_BIT);
		
	/* now set NVRAM inactive with GPIO0/1 both high */
	S24C16_stop(np, &gpreg);
	
	/* activate NVRAM */
	S24C16_start(np, &gpreg);

	/* write device code and random address MSB */
	S24C16_write_byte(np, &ack_data,
		0xa0 | ((offset >> 7) & 0x0e), &gpreg, &gpcntl);
	if (ack_data & 0x01)
		goto out;

	/* write random address LSB */
	S24C16_write_byte(np, &ack_data,
		offset & 0xff, &gpreg, &gpcntl);
	if (ack_data & 0x01)
		goto out;

	/* regenerate START state to set up for reading */
	S24C16_start(np, &gpreg);
	
	/* rewrite device code and address MSB with read bit set (lsb = 0x01) */
	S24C16_write_byte(np, &ack_data,
		0xa1 | ((offset >> 7) & 0x0e), &gpreg, &gpcntl);
	if (ack_data & 0x01)
		goto out;

	/* now set up GPIO0 for inputting data */
	gpcntl |= 0x01;
	OUTB(np, nc_gpcntl, gpcntl);
		
	/* input all requested data - only part of total NVRAM */
	for (x = 0; x < len; x++) 
		S24C16_read_byte(np, &data[x], (x == (len-1)), &gpreg, &gpcntl);

	/* finally put NVRAM back in inactive mode */
	gpcntl &= 0xfe;
	OUTB(np, nc_gpcntl, gpcntl);
	S24C16_stop(np, &gpreg);
	retv = 0;
out:
	/* return GPIO0/1 to original states after having accessed NVRAM */
	OUTB(np, nc_gpcntl, old_gpcntl);
	OUTB(np, nc_gpreg,  old_gpreg);

	return retv;
}