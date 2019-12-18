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
struct r820t_priv {int dummy; } ;

/* Variables and functions */
 int r820t_multi_read (struct r820t_priv*) ; 
 int r820t_write_reg_mask (struct r820t_priv*,int,int,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int r820t_vga_adjust(struct r820t_priv *priv)
{
	int rc;
	u8 vga_count;

	/* increase vga power to let image significant */
	for (vga_count = 12; vga_count < 16; vga_count++) {
		rc = r820t_write_reg_mask(priv, 0x0c, vga_count, 0x0f);
		if (rc < 0)
			return rc;

		usleep_range(10000, 11000);

		rc = r820t_multi_read(priv);
		if (rc < 0)
			return rc;

		if (rc > 40 * 4)
			break;
	}

	return 0;
}