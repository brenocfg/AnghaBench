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
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  S626_CRBMSK_INTCTRL ; 
 int /*<<< orphan*/  S626_LP_CRB (unsigned int) ; 
 int /*<<< orphan*/  S626_SET_CRB_INTRESETCMD (int) ; 
 int /*<<< orphan*/  S626_SET_CRB_INTRESET_A (int) ; 
 int /*<<< orphan*/  S626_SET_CRB_INTRESET_B (int) ; 
 int /*<<< orphan*/  s626_debi_replace (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void s626_reset_cap_flags(struct comedi_device *dev,
				 unsigned int chan)
{
	u16 set;

	set = S626_SET_CRB_INTRESETCMD(1);
	if (chan < 3)
		set |= S626_SET_CRB_INTRESET_A(1);
	else
		set |= S626_SET_CRB_INTRESET_B(1);

	s626_debi_replace(dev, S626_LP_CRB(chan), ~S626_CRBMSK_INTCTRL, set);
}