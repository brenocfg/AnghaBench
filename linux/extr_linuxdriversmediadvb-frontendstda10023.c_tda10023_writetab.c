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
typedef  int u8 ;
struct tda10023_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  tda10023_writebit (struct tda10023_state*,int,int,int) ; 

__attribute__((used)) static void tda10023_writetab(struct tda10023_state* state, u8* tab)
{
	u8 r,m,v;
	while (1) {
		r=*tab++;
		m=*tab++;
		v=*tab++;
		if (r==0xff) {
			if (m==0xff)
				break;
			else
				msleep(m);
		}
		else
			tda10023_writebit(state,r,m,v);
	}
}