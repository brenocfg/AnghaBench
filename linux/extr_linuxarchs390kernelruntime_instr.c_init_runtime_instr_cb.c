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
struct runtime_instr_cb {int rla; int s; int k; int ps; int pc; int v; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_DEFAULT_KEY ; 

__attribute__((used)) static void init_runtime_instr_cb(struct runtime_instr_cb *cb)
{
	cb->rla = 0xfff;
	cb->s = 1;
	cb->k = 1;
	cb->ps = 1;
	cb->pc = 1;
	cb->key = PAGE_DEFAULT_KEY;
	cb->v = 1;
}