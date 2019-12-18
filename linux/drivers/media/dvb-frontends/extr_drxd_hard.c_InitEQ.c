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
struct drxd_state {int /*<<< orphan*/  m_InitEQ; } ;

/* Variables and functions */
 int WriteTable (struct drxd_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int InitEQ(struct drxd_state *state)
{
	return WriteTable(state, state->m_InitEQ);
}