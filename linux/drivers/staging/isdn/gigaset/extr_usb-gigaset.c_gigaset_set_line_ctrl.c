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
struct cardstate {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  CS5 131 
#define  CS6 130 
#define  CS7 129 
#define  CS8 128 
 unsigned int CSIZE ; 
 unsigned int CSTOPB ; 
 unsigned int PARENB ; 
 unsigned int PARODD ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int set_value (struct cardstate*,int,int) ; 

__attribute__((used)) static int gigaset_set_line_ctrl(struct cardstate *cs, unsigned cflag)
{
	u16 val = 0;

	/* set the parity */
	if (cflag & PARENB)
		val |= (cflag & PARODD) ? 0x10 : 0x20;

	/* set the number of data bits */
	switch (cflag & CSIZE) {
	case CS5:
		val |= 5 << 8; break;
	case CS6:
		val |= 6 << 8; break;
	case CS7:
		val |= 7 << 8; break;
	case CS8:
		val |= 8 << 8; break;
	default:
		dev_err(cs->dev, "CSIZE was not CS5-CS8, using default of 8\n");
		val |= 8 << 8;
		break;
	}

	/* set the number of stop bits */
	if (cflag & CSTOPB) {
		if ((cflag & CSIZE) == CS5)
			val |= 1; /* 1.5 stop bits */
		else
			val |= 2; /* 2 stop bits */
	}

	return set_value(cs, 3, val);
}