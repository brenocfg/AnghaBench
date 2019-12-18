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
struct csis_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  S5PCSIS_CTRL ; 
 int S5PCSIS_CTRL_RESET ; 
 int s5pcsis_read (struct csis_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s5pcsis_write (struct csis_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void s5pcsis_reset(struct csis_state *state)
{
	u32 val = s5pcsis_read(state, S5PCSIS_CTRL);

	s5pcsis_write(state, S5PCSIS_CTRL, val | S5PCSIS_CTRL_RESET);
	udelay(10);
}