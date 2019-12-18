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
struct dce_hwseq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  D1VGA_CONTROL ; 
 int /*<<< orphan*/  D2VGA_CONTROL ; 
 int /*<<< orphan*/  D3VGA_CONTROL ; 
 int /*<<< orphan*/  D4VGA_CONTROL ; 
 int /*<<< orphan*/  D5VGA_CONTROL ; 
 int /*<<< orphan*/  D6VGA_CONTROL ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void dcn20_disable_vga(
	struct dce_hwseq *hws)
{
	REG_WRITE(D1VGA_CONTROL, 0);
	REG_WRITE(D2VGA_CONTROL, 0);
	REG_WRITE(D3VGA_CONTROL, 0);
	REG_WRITE(D4VGA_CONTROL, 0);
	REG_WRITE(D5VGA_CONTROL, 0);
	REG_WRITE(D6VGA_CONTROL, 0);
}