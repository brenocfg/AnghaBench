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
typedef  int u16 ;
struct cardstate {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  B115200 137 
#define  B1200 136 
#define  B19200 135 
#define  B2400 134 
#define  B300 133 
#define  B38400 132 
#define  B4800 131 
#define  B57600 130 
#define  B600 129 
#define  B9600 128 
 unsigned int CBAUD ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int set_value (struct cardstate*,int,int) ; 

__attribute__((used)) static int gigaset_baud_rate(struct cardstate *cs, unsigned cflag)
{
	u16 val;
	u32 rate;

	cflag &= CBAUD;

	switch (cflag) {
	case    B300: rate =     300; break;
	case    B600: rate =     600; break;
	case   B1200: rate =    1200; break;
	case   B2400: rate =    2400; break;
	case   B4800: rate =    4800; break;
	case   B9600: rate =    9600; break;
	case  B19200: rate =   19200; break;
	case  B38400: rate =   38400; break;
	case  B57600: rate =   57600; break;
	case B115200: rate =  115200; break;
	default:
		rate =  9600;
		dev_err(cs->dev, "unsupported baudrate request 0x%x,"
			" using default of B9600\n", cflag);
	}

	val = 0x383fff / rate + 1;

	return set_value(cs, 1, val);
}