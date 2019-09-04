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
typedef  int /*<<< orphan*/  u_char ;
struct IsdnCardState {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITEJADE (struct IsdnCardState*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  waitforCEC (struct IsdnCardState*,int,int) ; 

__attribute__((used)) static inline void
WriteJADECMDR(struct IsdnCardState *cs, int jade, int reg, u_char data)
{
	waitforCEC(cs, jade, reg);
	WRITEJADE(cs, jade, reg, data);
}