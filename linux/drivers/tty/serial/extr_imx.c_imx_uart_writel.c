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
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ membase; } ;
struct imx_port {int ucr1; int ucr2; int ucr3; int ucr4; int ufcr; TYPE_1__ port; } ;

/* Variables and functions */
#define  UCR1 132 
#define  UCR2 131 
#define  UCR3 130 
#define  UCR4 129 
#define  UFCR 128 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void imx_uart_writel(struct imx_port *sport, u32 val, u32 offset)
{
	switch (offset) {
	case UCR1:
		sport->ucr1 = val;
		break;
	case UCR2:
		sport->ucr2 = val;
		break;
	case UCR3:
		sport->ucr3 = val;
		break;
	case UCR4:
		sport->ucr4 = val;
		break;
	case UFCR:
		sport->ufcr = val;
		break;
	default:
		break;
	}
	writel(val, sport->port.membase + offset);
}