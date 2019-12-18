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
 int /*<<< orphan*/  D1VGA_MODE_ENABLE ; 
 int /*<<< orphan*/  D2VGA_CONTROL ; 
 int /*<<< orphan*/  D2VGA_MODE_ENABLE ; 
 int /*<<< orphan*/  D3VGA_CONTROL ; 
 int /*<<< orphan*/  D3VGA_MODE_ENABLE ; 
 int /*<<< orphan*/  D4VGA_CONTROL ; 
 int /*<<< orphan*/  D4VGA_MODE_ENABLE ; 
 int /*<<< orphan*/  REG_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VGA_TEST_CONTROL ; 
 int /*<<< orphan*/  VGA_TEST_ENABLE ; 
 int /*<<< orphan*/  VGA_TEST_RENDER_START ; 

__attribute__((used)) static void dcn10_disable_vga(
	struct dce_hwseq *hws)
{
	unsigned int in_vga1_mode = 0;
	unsigned int in_vga2_mode = 0;
	unsigned int in_vga3_mode = 0;
	unsigned int in_vga4_mode = 0;

	REG_GET(D1VGA_CONTROL, D1VGA_MODE_ENABLE, &in_vga1_mode);
	REG_GET(D2VGA_CONTROL, D2VGA_MODE_ENABLE, &in_vga2_mode);
	REG_GET(D3VGA_CONTROL, D3VGA_MODE_ENABLE, &in_vga3_mode);
	REG_GET(D4VGA_CONTROL, D4VGA_MODE_ENABLE, &in_vga4_mode);

	if (in_vga1_mode == 0 && in_vga2_mode == 0 &&
			in_vga3_mode == 0 && in_vga4_mode == 0)
		return;

	REG_WRITE(D1VGA_CONTROL, 0);
	REG_WRITE(D2VGA_CONTROL, 0);
	REG_WRITE(D3VGA_CONTROL, 0);
	REG_WRITE(D4VGA_CONTROL, 0);

	/* HW Engineer's Notes:
	 *  During switch from vga->extended, if we set the VGA_TEST_ENABLE and
	 *  then hit the VGA_TEST_RENDER_START, then the DCHUBP timing gets updated correctly.
	 *
	 *  Then vBIOS will have it poll for the VGA_TEST_RENDER_DONE and unset
	 *  VGA_TEST_ENABLE, to leave it in the same state as before.
	 */
	REG_UPDATE(VGA_TEST_CONTROL, VGA_TEST_ENABLE, 1);
	REG_UPDATE(VGA_TEST_CONTROL, VGA_TEST_RENDER_START, 1);
}