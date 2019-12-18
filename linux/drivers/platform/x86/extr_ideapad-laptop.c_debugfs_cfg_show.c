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
struct seq_file {struct ideapad_private* private; } ;
struct ideapad_private {int cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFG_3G_BIT ; 
 int /*<<< orphan*/  CFG_BT_BIT ; 
 int /*<<< orphan*/  CFG_CAMERA_BIT ; 
 int /*<<< orphan*/  CFG_WIFI_BIT ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int debugfs_cfg_show(struct seq_file *s, void *data)
{
	struct ideapad_private *priv = s->private;

	if (!priv) {
		seq_printf(s, "cfg: N/A\n");
	} else {
		seq_printf(s, "cfg: 0x%.8lX\n\nCapability: ",
			   priv->cfg);
		if (test_bit(CFG_BT_BIT, &priv->cfg))
			seq_printf(s, "Bluetooth ");
		if (test_bit(CFG_3G_BIT, &priv->cfg))
			seq_printf(s, "3G ");
		if (test_bit(CFG_WIFI_BIT, &priv->cfg))
			seq_printf(s, "Wireless ");
		if (test_bit(CFG_CAMERA_BIT, &priv->cfg))
			seq_printf(s, "Camera ");
		seq_printf(s, "\nGraphic: ");
		switch ((priv->cfg)&0x700) {
		case 0x100:
			seq_printf(s, "Intel");
			break;
		case 0x200:
			seq_printf(s, "ATI");
			break;
		case 0x300:
			seq_printf(s, "Nvidia");
			break;
		case 0x400:
			seq_printf(s, "Intel and ATI");
			break;
		case 0x500:
			seq_printf(s, "Intel and Nvidia");
			break;
		}
		seq_printf(s, "\n");
	}
	return 0;
}