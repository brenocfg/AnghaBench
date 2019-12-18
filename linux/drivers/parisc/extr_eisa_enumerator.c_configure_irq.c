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
typedef  int u_int8_t ;

/* Variables and functions */
 int HPEE_IRQ_CHANNEL_MASK ; 
 int HPEE_IRQ_MAX_ENT ; 
 int HPEE_IRQ_MORE ; 
 int HPEE_IRQ_TRIG_LEVEL ; 
 int /*<<< orphan*/  eisa_make_irq_edge (int) ; 
 int /*<<< orphan*/  eisa_make_irq_level (int) ; 
 int get_8 (unsigned char const*) ; 
 int /*<<< orphan*/  pr_cont (char*,int) ; 

__attribute__((used)) static int configure_irq(const unsigned char *buf)
{
	int len;
	u_int8_t c;
	int i;
	
	len=0;
	
	for (i=0;i<HPEE_IRQ_MAX_ENT;i++) {
		c = get_8(buf+len);
		
		pr_cont("IRQ %d ", c & HPEE_IRQ_CHANNEL_MASK);
		if (c & HPEE_IRQ_TRIG_LEVEL) {
			eisa_make_irq_level(c & HPEE_IRQ_CHANNEL_MASK);
		} else {
			eisa_make_irq_edge(c & HPEE_IRQ_CHANNEL_MASK);
		}
		
		len+=2; 
		/* hpux seems to allow for
		 * two bytes of irq data but only defines one of
		 * them, I think */
		if  (!(c & HPEE_IRQ_MORE)) {
			break;
		}
	}
	
	return len;
}