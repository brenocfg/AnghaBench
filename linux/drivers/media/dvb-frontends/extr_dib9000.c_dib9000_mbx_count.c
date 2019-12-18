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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct dib9000_state {int dummy; } ;

/* Variables and functions */
 int dib9000_read_word_attr (struct dib9000_state*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 dib9000_mbx_count(struct dib9000_state *state, u8 risc_id, u16 attr)
{
	if (risc_id == 0)
		return (u8) (dib9000_read_word_attr(state, 1028, attr) >> 10) & 0x1f;	/* 5 bit field */
	else
		return (u8) (dib9000_read_word_attr(state, 1044, attr) >> 8) & 0x7f;	/* 7 bit field */
}