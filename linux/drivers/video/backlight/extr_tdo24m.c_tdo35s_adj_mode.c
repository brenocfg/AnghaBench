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
struct tdo24m {int mode; } ;

/* Variables and functions */
 int EINVAL ; 
#define  MODE_QVGA 129 
#define  MODE_VGA 128 
 int /*<<< orphan*/  lcd_panel_config ; 
 int /*<<< orphan*/  lcd_qvga_pass_through_tdo35s ; 
 int /*<<< orphan*/  lcd_qvga_transfer ; 
 int /*<<< orphan*/  lcd_vga_pass_through_tdo35s ; 
 int /*<<< orphan*/  lcd_vga_transfer_tdo35s ; 
 int /*<<< orphan*/  tdo24m_writes (struct tdo24m*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tdo35s_adj_mode(struct tdo24m *lcd, int mode)
{
	switch (mode) {
	case MODE_VGA:
		tdo24m_writes(lcd, lcd_vga_pass_through_tdo35s);
		tdo24m_writes(lcd, lcd_panel_config);
		tdo24m_writes(lcd, lcd_vga_transfer_tdo35s);
		break;
	case MODE_QVGA:
		tdo24m_writes(lcd, lcd_qvga_pass_through_tdo35s);
		tdo24m_writes(lcd, lcd_panel_config);
		tdo24m_writes(lcd, lcd_qvga_transfer);
		break;
	default:
		return -EINVAL;
	}

	lcd->mode = mode;
	return 0;
}