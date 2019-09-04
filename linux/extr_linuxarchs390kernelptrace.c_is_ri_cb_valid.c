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
struct runtime_instr_cb {int rca; int roa; int rla; int s; int k; scalar_t__ h; scalar_t__ reserved1; int ps; scalar_t__ qs; int pc; scalar_t__ qc; scalar_t__ reserved2; scalar_t__ key; scalar_t__ reserved3; scalar_t__ reserved4; scalar_t__ reserved5; scalar_t__ reserved6; scalar_t__ reserved7; scalar_t__ reserved8; int m; } ;

/* Variables and functions */
 scalar_t__ PAGE_DEFAULT_KEY ; 

__attribute__((used)) static bool is_ri_cb_valid(struct runtime_instr_cb *cb)
{
	return (cb->rca & 0x1f) == 0 &&
		(cb->roa & 0xfff) == 0 &&
		(cb->rla & 0xfff) == 0xfff &&
		cb->s == 1 &&
		cb->k == 1 &&
		cb->h == 0 &&
		cb->reserved1 == 0 &&
		cb->ps == 1 &&
		cb->qs == 0 &&
		cb->pc == 1 &&
		cb->qc == 0 &&
		cb->reserved2 == 0 &&
		cb->key == PAGE_DEFAULT_KEY &&
		cb->reserved3 == 0 &&
		cb->reserved4 == 0 &&
		cb->reserved5 == 0 &&
		cb->reserved6 == 0 &&
		cb->reserved7 == 0 &&
		cb->reserved8 == 0 &&
		cb->rla >= cb->roa &&
		cb->rca >= cb->roa &&
		cb->rca <= cb->rla+1 &&
		cb->m < 3;
}