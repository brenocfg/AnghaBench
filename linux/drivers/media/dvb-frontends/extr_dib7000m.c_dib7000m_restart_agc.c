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
struct dib7000m_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dib7000m_write_word (struct dib7000m_state*,int,int) ; 

__attribute__((used)) static void dib7000m_restart_agc(struct dib7000m_state *state)
{
	// P_restart_iqc & P_restart_agc
	dib7000m_write_word(state, 898, 0x0c00);
	dib7000m_write_word(state, 898, 0x0000);
}