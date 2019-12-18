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
struct comedi_device {int dummy; } ;

/* Variables and functions */
 unsigned short NISTC_AI_STATUS1_OVER ; 
 unsigned short NISTC_AI_STATUS1_SC_TC ; 
 unsigned short NISTC_AI_STATUS1_START ; 
 unsigned short NISTC_AI_STATUS1_START1 ; 
 unsigned short NISTC_AI_STATUS1_STOP ; 
 unsigned short NISTC_INTA_ACK_AI_ERR ; 
 unsigned short NISTC_INTA_ACK_AI_SC_TC ; 
 unsigned short NISTC_INTA_ACK_AI_START ; 
 unsigned short NISTC_INTA_ACK_AI_START1 ; 
 unsigned short NISTC_INTA_ACK_AI_STOP ; 
 int /*<<< orphan*/  NISTC_INTA_ACK_REG ; 
 int /*<<< orphan*/  ni_stc_writew (struct comedi_device*,unsigned short,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ack_a_interrupt(struct comedi_device *dev, unsigned short a_status)
{
	unsigned short ack = 0;

	if (a_status & NISTC_AI_STATUS1_SC_TC)
		ack |= NISTC_INTA_ACK_AI_SC_TC;
	if (a_status & NISTC_AI_STATUS1_START1)
		ack |= NISTC_INTA_ACK_AI_START1;
	if (a_status & NISTC_AI_STATUS1_START)
		ack |= NISTC_INTA_ACK_AI_START;
	if (a_status & NISTC_AI_STATUS1_STOP)
		ack |= NISTC_INTA_ACK_AI_STOP;
	if (a_status & NISTC_AI_STATUS1_OVER)
		ack |= NISTC_INTA_ACK_AI_ERR;
	if (ack)
		ni_stc_writew(dev, ack, NISTC_INTA_ACK_REG);
}