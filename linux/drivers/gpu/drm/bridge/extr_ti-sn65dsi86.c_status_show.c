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
struct ti_sn_bridge {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;
struct seq_file {struct ti_sn_bridge* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,unsigned int,unsigned int*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int status_show(struct seq_file *s, void *data)
{
	struct ti_sn_bridge *pdata = s->private;
	unsigned int reg, val;

	seq_puts(s, "STATUS REGISTERS:\n");

	pm_runtime_get_sync(pdata->dev);

	/* IRQ Status Registers, see Table 31 in datasheet */
	for (reg = 0xf0; reg <= 0xf8; reg++) {
		regmap_read(pdata->regmap, reg, &val);
		seq_printf(s, "[0x%02x] = 0x%08x\n", reg, val);
	}

	pm_runtime_put(pdata->dev);

	return 0;
}