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
struct dib7000m_state {int dummy; } ;

/* Variables and functions */
 int dib7000m_read_word (struct dib7000m_state*,int) ; 
 int /*<<< orphan*/  dprintk (char*) ; 

__attribute__((used)) static int dib7000m_autosearch_irq(struct dib7000m_state *state, u16 reg)
{
	u16 irq_pending = dib7000m_read_word(state, reg);

	if (irq_pending & 0x1) { // failed
		dprintk("autosearch failed\n");
		return 1;
	}

	if (irq_pending & 0x2) { // succeeded
		dprintk("autosearch succeeded\n");
		return 2;
	}
	return 0; // still pending
}