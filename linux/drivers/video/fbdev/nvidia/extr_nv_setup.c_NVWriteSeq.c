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
typedef  int /*<<< orphan*/  u8 ;
struct nvidia_par {int /*<<< orphan*/  PVIO; } ;

/* Variables and functions */
 int /*<<< orphan*/  VGA_SEQ_D ; 
 int /*<<< orphan*/  VGA_SEQ_I ; 
 int /*<<< orphan*/  VGA_WR08 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void NVWriteSeq(struct nvidia_par *par, u8 index, u8 value)
{
	VGA_WR08(par->PVIO, VGA_SEQ_I, index);
	VGA_WR08(par->PVIO, VGA_SEQ_D, value);
}