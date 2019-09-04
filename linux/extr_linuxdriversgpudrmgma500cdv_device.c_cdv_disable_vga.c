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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VGACNTRL ; 
 int /*<<< orphan*/  VGA_DISP_DISABLE ; 
 int /*<<< orphan*/  VGA_SR_DATA ; 
 int /*<<< orphan*/  VGA_SR_INDEX ; 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void cdv_disable_vga(struct drm_device *dev)
{
	u8 sr1;
	u32 vga_reg;

	vga_reg = VGACNTRL;

	outb(1, VGA_SR_INDEX);
	sr1 = inb(VGA_SR_DATA);
	outb(sr1 | 1<<5, VGA_SR_DATA);
	udelay(300);

	REG_WRITE(vga_reg, VGA_DISP_DISABLE);
	REG_READ(vga_reg);
}